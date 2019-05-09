#include "Vision.h"

int findObstacle(cv::Mat &img, double threshold)
{
    cv::imshow("Depth",img);
    
    cv::Mat roi = img(cv::Rect(0,40,320,160)).clone();
    
    float pixCnt = 320*160;
    
    cv::threshold(roi,roi,1000,255,cv::THRESH_TOZERO_INV);
    cv::threshold(roi,roi,1,255,cv::THRESH_BINARY);
    
    cv::Moments m = cv::moments(roi,true);
    
    if (m.m00/pixCnt > threshold)
    {
        float x = m.m10/m.m00;
        if (x < 100)
        {
            return 2;
        }
        else if (x > 220)
        {
            return 3;
        }
        return 1;
    }
    
	return 0;
}
