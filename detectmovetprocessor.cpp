#include "detectmovetprocessor.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv4/opencv2/opencv.hpp"


using namespace cv;
DetectMovetProcessor::DetectMovetProcessor(int frameTrainCup):m_frameTrainCup{frameTrainCup},m_frameCounter{0},m_trainOver{false}
{
    pMOG2 = createBackgroundSubtractorMOG2(frameTrainCup, 16, true);

}

void DetectMovetProcessor::Run(const Mat &inputFrame, cv::Mat& outputFrame)
{
    Mat greyMat;
    cvtColor(inputFrame, greyMat, COLOR_BGR2GRAY);
    imshow("raz",greyMat);
    if(!m_trainOver)
        pMOG2->apply(greyMat, outputFrame,0.001); // apply background subtractor
    else
        pMOG2->apply(greyMat, outputFrame,0.0003); // apply background subtractor

    m_frameCounter++;
    if (!m_trainOver && m_frameCounter >= m_frameTrainCup) {       // train background subtractor
        m_trainOver = true;
    }
}

bool DetectMovetProcessor::isTrainOver()
{
    return m_trainOver;
}
