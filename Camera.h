#pragma once
#include <opencv2/opencv.hpp>
#include <OpenNI.h>

class Camera
{
protected:
    openni::Device            m_device;
    openni::VideoStream        m_depthStream;
    openni::VideoStream        m_colorStream;
    openni::VideoFrameRef    m_depthFrame;
    openni::VideoFrameRef    m_colorFrame;
    bool m_flagInitSuccessful;
    bool m_flagShowImage;
public:
	Camera();
    ~Camera();
	cv::Mat getDepth();
};
