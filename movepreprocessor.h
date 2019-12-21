#include "preprocessor.h"
#include <opencv2/imgproc.hpp>

#ifndef MOVEPREPROCESSOR_H
#define MOVEPREPROCESSOR_H


class MovePreProcessor:PreProcessor
{
public:
    MovePreProcessor();
    virtual void Run(const cv::Mat &, cv::Mat &) override;
};

#endif // MOVEPREPROCESSOR_H
