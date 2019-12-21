#include <iostream>
#include<string>
#include<vector>


#include "center.h"
#include "path.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv4/opencv2/opencv.hpp"

#include"detectmovetprocessor.h"
#include"findcarprocessor.h"
#include"checkcarinarea.h"
#include"filtermovedetectframe.h"
#include"movepreprocessor.h"
#include "checkpeopleprocessor.h"

#include "light.h"
#include "lightcontroller.h"
#include "lightgroup.h"



using namespace std;
using namespace cv;




int main()
{
    VideoCapture cap("testVideo.mkv");

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    namedWindow( "Frame", WINDOW_NORMAL );// Create a window for display.
    Mat frame;


    // Capture frame-by-frame
    cap >> frame;

    MovePreProcessor A1proc;
    DetectMovetProcessor Bproc{500};
    FindCarProcessor Dproc{500,4000};

    std::vector<std::vector<cv::Point> > carPoints;
    carPoints.push_back(std::vector<cv::Point> {Point{600,40},
                                               Point{650,40},
                                               Point{650,250},
                                               Point{600,250}});

    carPoints.push_back(std::vector<cv::Point> {Point{650,460},
                                               Point{700,460},
                                               Point{700,700},
                                               Point{650,700}});

    carPoints.push_back(std::vector<cv::Point> {Point{135,340},
                                               Point{500,340},
                                               Point{500,400},
                                               Point{135,400}});

    carPoints.push_back(std::vector<cv::Point> {Point{750,300},
                                               Point{1100,300},
                                               Point{1100,365},
                                               Point{750,365}});

    FilterMoveDetectFrame Fproc1;

    std::vector<std::vector<cv::Point> > points;
    points.push_back(std::vector<cv::Point> {Point{530,260},
                                               Point{560,260},
                                               Point{560,280},
                                               Point{530,280}});

    points.push_back(std::vector<cv::Point> {Point{700,263},
                                               Point{722,263},
                                               Point{722,277},
                                               Point{700,277}});

    points.push_back(std::vector<cv::Point> {Point{732,284},
                                               Point{760,284},
                                               Point{760,300},
                                               Point{732,300}});

    points.push_back(std::vector<cv::Point> {Point{744,407},
                                               Point{771,407},
                                               Point{771,423},
                                               Point{744,423}});

    points.push_back(std::vector<cv::Point> {Point{720,424},
                                               Point{750,424},
                                               Point{750,464},
                                               Point{720,464}});

    points.push_back(std::vector<cv::Point> {Point{521,438},
                                               Point{541,438},
                                               Point{541,459},
                                               Point{521,459}});

    points.push_back(std::vector<cv::Point> {Point{489,411},
                                               Point{523,411},
                                               Point{523,436},
                                               Point{489,436}});

    points.push_back(std::vector<cv::Point> {Point{509,274},
                                               Point{523,274},
                                               Point{523,297},
                                               Point{523,297}});


    vector <Light> trafficLights{
        {Point{650,250},55},
        {Point{800,300},55},
        {Point{650,460},55},
        {Point{450,300},55}

    };
    CheckCarInArea Eproc{frame.size(),carPoints,&trafficLights};

    vector <Light> peopleLights{
        {Point{560,260},55},
        {Point{700,263},55},
        {Point{760,284},55},
        {Point{744,407},55},

        {Point{720,424},55},
        {Point{521,438},55},
        {Point{489,411},55},
        {Point{509,274},55},

    };

    CheckPeopleProcessor Gproc(frame.size(),points,&peopleLights);


    vector<LightGroup> lightsGroup{
        {&peopleLights[0],
            {&peopleLights[1]},
            {&trafficLights[0],&trafficLights[2]},false},

        {&peopleLights[1],
            {&peopleLights[0]},
            {&trafficLights[0],&trafficLights[2]},false},

        {&trafficLights[0],
            {&trafficLights[2],&peopleLights[2],&peopleLights[3],&peopleLights[6],&peopleLights[7]},
            {&trafficLights[1],&trafficLights[3],&peopleLights[0],&peopleLights[1],&peopleLights[4],&peopleLights[5]},false},

        {&peopleLights[2],
            {&peopleLights[3]},
            {&trafficLights[1],&trafficLights[3]},false},

        {&peopleLights[3],
            {&peopleLights[2]},
            {&trafficLights[1],&trafficLights[3]},false},


        {&trafficLights[1],
            {&trafficLights[3],&peopleLights[0],&peopleLights[1],&peopleLights[5],&peopleLights[4]},
            {&trafficLights[0],&trafficLights[2],&peopleLights[2],&peopleLights[3],&peopleLights[6],&peopleLights[7]},false},


        {&peopleLights[4],
            {&peopleLights[5]},
            {&trafficLights[2],&trafficLights[0]},false},

        {&peopleLights[5],
            {&peopleLights[4]},
            {&trafficLights[2],&trafficLights[0]},false},


        {&trafficLights[2],
            {&trafficLights[0],&peopleLights[2],&peopleLights[3],&peopleLights[6],&peopleLights[7]},
            {&trafficLights[1],&trafficLights[3],&peopleLights[0],&peopleLights[1],&peopleLights[5],&peopleLights[4]},false},

        {&peopleLights[6],
            {&peopleLights[7]},
            {&trafficLights[3],&trafficLights[1]},false},

        {&peopleLights[7],
            {&peopleLights[6]},
            {&trafficLights[3],&trafficLights[1]},false},

        {&trafficLights[3],
            {&trafficLights[1],&peopleLights[0],&peopleLights[1],&peopleLights[4],&peopleLights[5]},
            {&trafficLights[0],&trafficLights[2],&peopleLights[2],&peopleLights[3],&peopleLights[6],&peopleLights[7]},false}

    };
    LightController lightController{lightsGroup,false};

    vector<Rect> countours;
    vector<Center> centers;
    vector<Path> inputPaths;

    bool firstCeheck{false};
    while(1){


        Mat out;
        Mat out2;

        // Capture frame-by-frame
        cap >> frame;



        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        //A1proc.Run(frame,frame);
        Bproc.Run(frame,out);

        Gproc.Run(out);


        Fproc1.Run(out,out);
        Dproc.Run(out,countours,centers,frame);

        Eproc.Run(inputPaths,centers);

        if(!firstCeheck){
            lightController.checkLights();
            firstCeheck = true;
        }
        lightController.Run(frame);


        for(auto countor:countours)
            rectangle(frame,countor,Scalar(0,255,255));
        for(auto path:inputPaths)
            path.DrawPath(frame);

        // Display the resulting frame
        imshow( "Frame", frame   );

        // Press  ESC on keyboard to exit
        char c=(char)waitKey(25);
        if(c==27)
            break;

    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;
}
