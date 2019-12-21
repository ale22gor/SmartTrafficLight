#ifndef LIGHTGROUP_H
#define LIGHTGROUP_H
#include <vector>
class Light;

struct LightGroup{

    Light* m_light;
    std::vector<Light*> m_friendlyLights;
    std::vector<Light*> m_oppositeLights;
    bool someLightIsOver;
};

#endif // LIGHTGROUP_H
