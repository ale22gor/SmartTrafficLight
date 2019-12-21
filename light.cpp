#include "light.h"

using namespace cv;

Light::Light(cv::Point coord, int timerCup):
    m_block{false},
    m_coord{coord},m_timerCup{timerCup},m_countDown{timerCup},
    m_activeTimer{0},m_color{cv::Scalar(0,0,255)},m_trafficAreaStatus{false},m_active{false}
{}

void Light::increaseTimer(LightGroup *m_myGroup){
    if(m_block || !m_active)
        return;
    m_activeTimer++;
    m_countDown = m_timerCup - m_activeTimer;
    if(m_countDown <= 15)
        setColor(YELLOW);


    if(m_countDown <= 0){
        setColor(RED);
        m_activeTimer = 0;
        m_countDown = m_timerCup;
        m_active = false;
        m_myGroup->someLightIsOver = true;
    }
}

void Light::setAreaStatus(bool value){
    m_trafficAreaStatus = value;
}

void Light::unBlock(){
    m_block = false;
}

void Light::block(){
    setColor(RED);
    m_active = false;
    m_block = true;
}

void Light::activate(){
    setColor(GREEN);
    m_active = true;
}

bool Light::isBlocked(){
    return m_block;
}

bool Light::isCarIN(){
    return m_trafficAreaStatus;
}

bool Light::isActive(){
    return m_active;
}

void Light::setColor(Light::TrafficColors color){
    switch(color){
    case RED:
        m_color = Scalar(0,0,255);
        break;
    case YELLOW:
        m_color = Scalar(0,255,255);
        break;
    case GREEN:
        m_color = Scalar(0,255,0);
        break;
    }

}

std::string Light::getTextCountDown(){
    return (textCountDown = std::to_string(m_countDown));
}

void Light::showLight(Mat &frame){
    textCountDown = std::to_string(m_countDown);
    circle(frame,m_coord,5,m_color,-1,0);
    putText(frame,textCountDown,Point{m_coord.x,m_coord.y+5},FONT_HERSHEY_DUPLEX,1,m_color,1);
}
