#include<vector>
#include <opencv2/core/mat.hpp>
#ifndef FINDCARPROCESSOR_H
#define FINDCARPROCESSOR_H
class Center;



class FindCarProcessor
{
    const int m_minObjectArea;
    const int m_maxObjectArea;
public:
    FindCarProcessor(int ,int );
    void Run(const cv::Mat &,std::vector<cv::Rect> &,std::vector<Center> &,cv::Mat);

};

#endif // FINDCARPROCESSOR_H
