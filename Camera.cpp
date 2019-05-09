#include "Camera.h"

Camera::Camera()
{
    m_flagInitSuccessful = m_flagShowImage = true;
    m_frameNum = m_frameIdx = 0;
    m_sensorType = 0;
    
    openni::Status rc = openni::STATUS_OK;
    
    openni::Device device;
    const char* deviceURI = openni::ANY_DEVICE;
    
    rc = openni::OpenNI::initialize();
    printf("After initialization:\n%s\n", openni::OpenNI::getExtendedError());
    
    rc = device.open(deviceURI);
    if (rc != openni::STATUS_OK)
    {
        printf("SimpleViewer: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
        openni::OpenNI::shutdown();
        exit(-1);
    }
    
    rc = depth.create(device, openni::SENSOR_DEPTH);
    if (rc == openni::STATUS_OK)
    {
        rc = depth.start();
        if (rc != openni::STATUS_OK)
        {
            printf("SimpleViewer: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
            depth.destroy();
        }
    }
    else
    {
        printf("SimpleViewer: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
    }
    
    rc = color.create(device, openni::SENSOR_COLOR);
    if (rc == openni::STATUS_OK)
    {
        rc = color.start();
        if (rc != openni::STATUS_OK)
        {
            printf("SimpleViewer: Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
            color.destroy();
        }
    }
    else
    {
        printf("SimpleViewer: Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
    }
    
    if (!depth.isValid() || !color.isValid())
    {
        printf("SimpleViewer: No valid streams. Exiting\n");
        openni::OpenNI::shutdown();
        exit(2);
    }
    
    openni::VideoMode depthVideoMode = m_depthStream.getVideoMode();
    openni::VideoMode colorVideoMode = m_colorStream.getVideoMode();
    m_depthWidth = depthVideoMode.getResolutionX();
    m_depthHeight = depthVideoMode.getResolutionY();
    m_colorWidth = colorVideoMode.getResolutionX();
    m_colorHeight = colorVideoMode.getResolutionY();
    cout << "Depth = (" << m_depthWidth << "," << m_depthHeight << ")" << endl;
    cout << "Color = (" << m_colorWidth << "," << m_colorHeight << ")" << endl;
    
    // Set exposure if needed
    m_colorStream.getCameraSettings()->setAutoWhiteBalanceEnabled(false);
    int exposure = m_colorStream.getCameraSettings()->getExposure();
    int delta = 100;
    m_colorStream.getCameraSettings()->setExposure(exposure + delta);
}

Camera::~Camera()
{
    m_depthStream.stop();
    m_colorStream.stop();
    m_depthStream.destroy();
    m_colorStream.destroy();
    m_device.close();
    openni::OpenNI::shutdown();
}

cv::Mat Camera::getDepth()
{
    m_depthStream.readFrame(&m_depthFrame);
    if (m_depthFrame.isValid())
    {
        cv::Mat mImageDepth(m_depthHeight, m_depthWidth, CV_16UC1, (void*)m_depthFrame.getData());
        cv::Mat cScaledDepth;
        mImageDepth.convertTo(cScaledDepth, CV_16UC1, c_depthScaleFactor);
        if (m_sensorType == 0)
            cv::flip(cScaledDepth, cScaledDepth, 1);
        return cScaledDepth;
    }
    else
    {
        cerr << "ERROR: Cannot read depth frame from depth stream. Quitting..." << endl;
        return cv::Mat();
    }
}
