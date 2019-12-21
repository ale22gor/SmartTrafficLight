#include "movepreprocessor.h"
using namespace cv;
MovePreProcessor::MovePreProcessor()
{

}

void MovePreProcessor::Run(const cv::Mat &inputFrame, cv::Mat &outputFrame)
{
   blur(inputFrame, outputFrame, Size(2, 2));

}
