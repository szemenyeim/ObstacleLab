#pragma once
#include <opencv2/opencv.hpp>
#include <OpenNI.h>

class Camera
{
protected:
    openni::Status rc;
	openni::Device device;
	openni::VideoStream depth;
	openni::VideoFrameRef frame;
public:
	Camera();
    ~Camera();
	cv::Mat getDepth();
};
