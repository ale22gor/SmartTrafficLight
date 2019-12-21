#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include "lightgroup.h"

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>


struct LightController{
    std::vector<LightGroup> m_lightGroups;
    bool someGroupIsOver;


    void Run(cv::Mat frame);
    void checkLights();

};

#endif // LIGHTCONTROLLER_H
