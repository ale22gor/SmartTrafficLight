#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#ifndef FILTERDETECTIONFRAME_H
#define FILTERDETECTIONFRAME_H


class FilterDetectionFrame
{
protected:
    cv::Mat closingElement;
    cv::Mat dilationElement;

    constexpr static int m_thresholdType = cv::THRESH_BINARY;
public:
    FilterDetectionFrame();
    virtual void Run(const cv::Mat&, cv::Mat&)=0;
    virtual ~FilterDetectionFrame();

};

#endif // FILTERDETECTIONFRAME_H
