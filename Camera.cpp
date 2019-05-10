#include "Camera.h"

#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms
using namespace openni;

Camera::Camera()
{
    rc = OpenNI::initialize();
	if (rc != STATUS_OK)
	{
		printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
		exit(-1);
	}

	rc = device.open(ANY_DEVICE);
	if (rc != STATUS_OK)
	{
		printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
		exit(-1);
	}

	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		rc = depth.create(device, SENSOR_DEPTH);
		if (rc != STATUS_OK)
		{
			printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
		    exit(-1);
		}
	}

	rc = depth.start();
	if (rc != STATUS_OK)
	{
		printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		exit(-1);
	}
}

Camera::~Camera()
{
    depth.stop();
    depth.destroy();
    device.close();
    OpenNI::shutdown();
}

cv::Mat Camera::getDepth()
{
    int changedStreamDummy;
    VideoStream* pStream = &depth;
    rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
    if (rc != STATUS_OK)
    {
        printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
        return cv::Mat();
    }

    rc = depth.readFrame(&frame);
    if (rc != STATUS_OK)
    {
        printf("Read failed!\n%s\n", OpenNI::getExtendedError());
        return cv::Mat();
    }

    if (frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
    {
        printf("Unexpected frame format\n");
        return cv::Mat();
    }
    if (frame.isValid())
    {
        cv::Mat mImageDepth(frame.getHeight(), frame.getWidth(), CV_16UC1, (void*)frame.getData());
        cv::Mat cScaledDepth;
        mImageDepth.convertTo(cScaledDepth, CV_16UC1, 5.0);
        cv::flip(cScaledDepth, cScaledDepth, 1);
        return cScaledDepth;
    }
    else
    {
        std::cerr << "ERROR: Cannot read depth frame from depth stream. Quitting..." << std::endl;
        return cv::Mat();
    }
}
