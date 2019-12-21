#include "checkcarinarea.h"
#include "center.h"
#include "path.h"
#include "light.h"

#include <opencv4/opencv2/opencv.hpp>



using namespace cv;
CheckCarInArea::CheckCarInArea(cv::Size videoSize, std::vector <std::vector<cv::Point> > points,std::vector<Light> *trafficLights):
    m_trafficLights{trafficLights}
{

    for(int i{0};i<points.size();++i)
        m_MaskAreas.push_back(cv::Mat::zeros(videoSize, CV_8UC1)); // create black image

    for(auto it = points.begin(); it != points.end(); ++it){
        fillConvexPoly(m_MaskAreas[std::distance(points.begin(),it)], *it, cv::Scalar(255), CV_8UC1, 0);
    }

}

void CheckCarInArea::Run(std::vector<Path> &inputPaths,
                         std::vector<Center> &inputCenters)
{
    for (Path &path : inputPaths) {

        int pointIndex{-1};
        int i{0};
        for (Center &carCenter : inputCenters) {

            if (path.CheckLength(carCenter.m_cordinates))
                pointIndex = i;
            i++;
        }
        if (pointIndex >= 0) {

            path.AddPoint(inputCenters[pointIndex].m_cordinates);
            inputCenters[pointIndex].m_isAdded = true;
            path.m_lostCarFrames = 0;
        } else {
            path.m_lostCarFrames++;
        }
    }

    inputCenters.erase(
                std::remove_if(inputCenters.begin(), inputCenters.end(),
                               [](Center center) { return center.m_isAdded; }),
            inputCenters.end());


    inputPaths.erase(std::remove_if(inputPaths.begin(), inputPaths.end(),
                                    [this](Path &path) {
        if (path.CheckLost())
            return true;
        for(size_t i{0};i<m_MaskAreas.size();i++){
            if (path.CheckInArea(m_MaskAreas[i]))
                (*m_trafficLights)[i].setAreaStatus(true);
            else
                (*m_trafficLights)[i].setAreaStatus(false);
        }
        return false;
    }),
                     inputPaths.end());

    inputPaths.insert(inputPaths.end(), inputCenters.begin(),
                      inputCenters.end());


}
