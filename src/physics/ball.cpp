#include "physics/ball.h"
#include <cmath>

#define WIDTH 1280
#define HEIGHT 720
#define EPS 1e-4f

static const float restitution = 0.8f ;
static const float friction = 0.008f ;

/*void ResolveImpulse(glm::vec2& vel , glm::vec2& normalVector) {
    float vn = glm::dot(vel , normalVector);
    if(vn > 0) return ;

    float jn = -(1 + restitution) * vn ;
    vel.x += jn * normalVector.x ;
    vel.y += jn * normalVector.y ;

    glm::vec2 tangentVector = {-normalVector.y , normalVector.x} ;
    float jt = -glm::dot(vel , tangentVector) ;
    float maxfriction = friction * jn ;
    if(jt > maxfriction) jt = maxfriction ;
    if(jt < -maxfriction) jt = -maxfriction ;

    vel.x += jt * tangentVector.x ;
    vel.y += jt * tangentVector.y ;
}*/

void Ball::integrate(float dt , glm::vec2& gravity) {
    glm::vec2 vel = (cur_pos - prev_pos) / dt ;
    prev_pos = cur_pos ;
    cur_pos += (vel + 0.5f*gravity*dt) * dt ;
}

void Ball::handleWallCollisions() {
    if(cur_pos.x > WIDTH - radius) {
        glm::vec2 displacement = cur_pos - prev_pos ;
        cur_pos = {WIDTH - radius , cur_pos.y} ;
        displacement.x = -(displacement.x) * restitution ;
        displacement.y = displacement.y * (1.0f - friction) ;
        prev_pos = cur_pos - displacement ;
    }
    if(cur_pos.x < radius) {
        glm::vec2 displacement = cur_pos - prev_pos ;
        cur_pos = {radius , cur_pos.y} ;
        displacement.x = -(displacement.x) * restitution ;
        displacement.y = displacement.y * (1.0f - friction) ;
        prev_pos = cur_pos - displacement ;
    }
    if(cur_pos.y > HEIGHT - radius) {
        glm::vec2 displacement = cur_pos - prev_pos ;
        cur_pos = {cur_pos.x , HEIGHT - radius} ;
        //displacement.x = displacement.x * (1.0f - friction) ;
        displacement.y = -(displacement.y) * restitution ;
        prev_pos = cur_pos - displacement ;
    }
    if(cur_pos.y < radius) {
        glm::vec2 displacement = cur_pos - prev_pos ;
        cur_pos = {cur_pos.x , radius} ;
        displacement.x = displacement.x * (1.0f - friction) ;
        displacement.y = -(displacement.y) * restitution ;
        prev_pos = cur_pos - displacement ;
    }
}

void Ball::applyGroundFriction() {
    if(cur_pos.y + radius >= HEIGHT - 0.01f) {
        glm::vec2 vel = cur_pos - prev_pos ;
        vel *= (1 - friction) ;
        if (glm::length(vel) < 0.001f) vel = glm::vec2(0.0f) ;
        prev_pos = cur_pos - vel ;
    }
}