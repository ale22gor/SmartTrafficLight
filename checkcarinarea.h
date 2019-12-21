#include<vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
class Center;
class Path;

#ifndef CHECKCARINAREA_H
#define CHECKCARINAREA_H

class Light;

class CheckCarInArea
{
    std::vector<Light> *m_trafficLights;
    std::vector<cv::Mat> m_MaskAreas;
public:
    CheckCarInArea(cv::Size, std::vector <std::vector<cv::Point> > points, std::vector<Light> *trafficLights);
    void Run(std::vector<Path> &, std::vector<Center> &);
};

#endif // CHECKCARINAREA_H
