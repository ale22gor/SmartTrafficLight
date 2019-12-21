#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#ifndef CHECKPEOPLEPROCESSOR_H
#define CHECKPEOPLEPROCESSOR_H

class Light;

class CheckPeopleProcessor
{
    std::vector<Light> *m_peopleLights;
    std::vector<cv::Mat> m_MaskAreas;

public:
    CheckPeopleProcessor(cv::Size,std::vector<std::vector<cv::Point> >& points,std::vector<Light> *peopleLights);
    void Run(cv::Mat inputFrame);
};

#endif // CHECKPEOPLEPROCESSOR_H
