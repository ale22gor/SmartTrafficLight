#include "lightcontroller.h"

#include "light.h"


void LightController::Run(cv::Mat frame){
    for(auto lightGroup:m_lightGroups){

        lightGroup.m_light->increaseTimer(&lightGroup);
        lightGroup.m_light->showLight(frame);



        if(lightGroup.someLightIsOver){
            for(auto oppositeLight:lightGroup.m_oppositeLights)
                oppositeLight->unBlock();
            someGroupIsOver = true;
        }

    }
    if(someGroupIsOver)
        checkLights();

}

void LightController::checkLights(){
    someGroupIsOver = false;
    //for(size_t i{0}; i<m_lightGroups.size();i++)
    for(auto lightGroup:m_lightGroups){
        if(lightGroup.m_light->isCarIN() &&
                !lightGroup.m_light->isBlocked() &&
                !lightGroup.m_light->isActive()){
            lightGroup.m_light->setColor(Light::GREEN);
            lightGroup.m_light->activate();
            for(auto friendLight:lightGroup.m_friendlyLights)
                friendLight->activate();
            for(auto oppositeLight:lightGroup.m_oppositeLights)
                oppositeLight->block();

        }
    }
    for(auto lightGroup:m_lightGroups){
        if(!lightGroup.m_light->isBlocked() && !lightGroup.m_light->isActive()){
            lightGroup.m_light->setColor(Light::GREEN);
            lightGroup.m_light->activate();
            for(auto friendLight:lightGroup.m_friendlyLights)
                friendLight->activate();
            for(auto oppositeLight:lightGroup.m_oppositeLights)
                oppositeLight->block();
        }
    }

    rotate(m_lightGroups.begin(), m_lightGroups.begin() + 1, m_lightGroups.end());


}
