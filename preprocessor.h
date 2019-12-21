#include<opencv4/opencv2/core/mat.hpp>

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H


class PreProcessor
{

public:
    PreProcessor();
    virtual void Run(const cv::Mat&, cv::Mat&)=0;
    virtual ~PreProcessor();
};

#endif // PREPROCESSOR_H
