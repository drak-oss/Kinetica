#pragma once
#include <glm/glm.hpp>

struct rgbaColor {
    float r , g , b , a ;
};

struct Ball {
    glm::vec2 prev_pos ;
    glm::vec2 cur_pos ;
    float radius ;
    rgbaColor color ;

    void integrate(float dt , glm::vec2& gravity) ;
    void handleWallCollisions() ;
    void applyGroundFriction() ;
};