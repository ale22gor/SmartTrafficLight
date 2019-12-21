#include "filterdetectionframe.h"
#ifndef FILTERMOVEDETECTFRAME_H
#define FILTERMOVEDETECTFRAME_H


class FilterMoveDetectFrame:public FilterDetectionFrame
{
    cv::Mat openingElement;
public:
    FilterMoveDetectFrame();
    void Run(const cv::Mat &, cv::Mat &) override;
};

#endif // FILTERMOVEDETECTFRAME_H
