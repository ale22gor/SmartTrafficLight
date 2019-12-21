#ifndef LIGHT_H
#define LIGHT_H
#include <opencv2/imgproc/imgproc.hpp>

#include "lightgroup.h"

class Light{
    bool m_block;

    cv::Point m_coord;
    int m_timerCup;
    int m_countDown;

    int m_activeTimer;

    cv::Scalar m_color;
    std::string textCountDown;
    bool m_trafficAreaStatus;
    bool m_active;

public:
    enum TrafficColors{RED,YELLOW,GREEN};
    enum Status{OK,NEXT};

    Light(cv::Point coord, int timerCup);
    void increaseTimer(LightGroup * m_myGroup);


    void setAreaStatus( bool value);
    void unBlock();
    void block();
    void activate();
    bool isBlocked();
    bool isCarIN();

    bool isActive();
    void setColor(TrafficColors color);
    std::string getTextCountDown();
    void showLight(cv::Mat& frame);
};
#endif // LIGHT_H
