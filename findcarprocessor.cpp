#include "findcarprocessor.h"
#include "opencv4/opencv2/opencv.hpp"
#include "center.h"


using namespace cv;
FindCarProcessor::FindCarProcessor(int min,int max):m_minObjectArea{min},m_maxObjectArea{max}
{

}

void FindCarProcessor::Run(const cv::Mat &inputFrame, std::vector<cv::Rect> &outputCountors, std::vector<Center> &outputCenters,Mat anotherInput)
{



    Mat dist;
    distanceTransform(inputFrame, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);

    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    Mat fg;
    threshold(dist, fg, 0.4, 1.0, THRESH_BINARY);
    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(4, 4, CV_8U);
    dilate(fg, fg, kernel1);



    Mat dist_8u;
    fg.convertTo(dist_8u, CV_8UC1);

    std::vector<std::vector<Point> > contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat markers = Mat::zeros(fg.size(), CV_32S);

    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i)+10), -1);
    }
    circle(markers, Point(5,5), 3, Scalar(255), -1);
    Mat bg;
    threshold(dist, bg, 0, 1, THRESH_BINARY_INV);
    //imshow("bg",bg);


    bg.convertTo(bg,CV_32SC1);

    markers = bg + markers;

    Mat loh;
    //imshow("loh",loh);

    watershed(anotherInput, markers);

/*
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int b = theRNG().uniform(0, 0);
            int g = theRNG().uniform(255, 255);
            int r = theRNG().uniform(0, 0);
            if(markers.at<int>(i,j) == -1)
                anotherInput.at<Vec3b>(i,j) = Vec3b((uchar)b, (uchar)g, (uchar)r);

        }
    }
*/

    //imshow("REZ", anotherInput);



    //std::vector<std::vector<Point> > contours;

    //contours.clear();
    markers.convertTo(markers,CV_8U);
    markers *= 100;
    threshold(markers,markers,0.1,255,THRESH_BINARY_INV);

    imshow("markers",markers);
    //return;

    contours.clear();
    std::vector<Vec4i> hierarchy;

    findContours(markers, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);


    //drawContours(anotherInput,contours2,);

    std::vector<Point> contours_poly(4);

    outputCountors.clear();
    outputCenters.clear();


    for (auto contour : contours) {
        //if(contourArea(contour) > m_maxObjectArea)
        //   continue;
        approxPolyDP(Mat{contour}, contours_poly, 3, true);
        boundingRect(Mat{contours_poly});

        Rect tmp{boundingRect(Mat{contours_poly})};
        if (tmp.area() < m_maxObjectArea && tmp.area() > m_minObjectArea) {
            outputCenters.push_back(
                        Center{(tmp.br() + tmp.tl()) *
                               0.5}); // save countour center
            outputCountors.push_back(std::move(tmp)); // save countour

        }
    }


}


