#include "checkpeopleprocessor.h"
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include "light.h"

using namespace cv;
CheckPeopleProcessor::CheckPeopleProcessor(Size videoSize,std::vector<std::vector<cv::Point> >& points,std::vector<Light> *peopleLights):
    m_peopleLights{peopleLights}
{
    for(size_t i{0};i<points.size();++i)
        m_MaskAreas.push_back(cv::Mat::zeros(videoSize, CV_8UC1)); // create black image

    for(auto it = points.begin(); it != points.end(); ++it){
        fillConvexPoly(m_MaskAreas[std::distance(points.begin(),it)], *it, cv::Scalar(255), CV_8UC1, 0);
    }
}

void CheckPeopleProcessor::Run(Mat inputFrame)
{

    for(size_t i{0};i<m_MaskAreas.size();i++){
        Mat tmp;
        inputFrame.copyTo(tmp,m_MaskAreas[i]);
        int areaPixels =  countNonZero(m_MaskAreas[i]);
        int peoplePixels = countNonZero(tmp);
        double peopleProcent = 1.0 - static_cast<double>(peoplePixels)/ static_cast<double>(areaPixels);
        if(peopleProcent > 0.85){
            (*m_peopleLights)[i].setAreaStatus(true);
        }else
             (*m_peopleLights)[i].setAreaStatus(false);

    }

}
