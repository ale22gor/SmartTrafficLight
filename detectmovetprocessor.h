#include<opencv4/opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/video/background_segm.hpp>


#ifndef DETECTMOVETPROCESSOR_H
#define DETECTMOVETPROCESSOR_H


class DetectMovetProcessor
{
    cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2; // MOG2 Background subtractor
    const int m_frameTrainCup;
    int m_frameCounter;
    bool m_trainOver;
public:
    DetectMovetProcessor(int frameTrainCup);
    void Run(const cv::Mat&, cv::Mat&);
    bool isTrainOver();
};

#endif // DETECTMOVETPROCESSOR_H
