#include "system.h"
#include "ball.h"

#define WIDTH 1280
#define HEIGHT 720

static const float restitution = 0.8f ;
static const float friction = 0.008f ;
static const int constraintIterations = 10 ;

void System::handleBallCollisions(std::vector<Ball>& balls) {
    const size_t n = balls.size() ;
    for(size_t i = 0 ; i < n ; i++) {
        for(size_t j = i + 1 ; j < n ; j++) {
            float dx = balls[j].cur_pos.x - balls[i].cur_pos.x , dy = balls[j].cur_pos.y - balls[i].cur_pos.y ;
            float dist2 = dx * dx + dy * dy , r = balls[i].radius + balls[j].radius ;
            if(dist2 >= r * r) continue ;

            float dist = sqrtf(dist2) ;
            if(dist == 0.0f) continue ;
            glm::vec2 normalVector = {dx / dist , dy / dist} ;
            
            float penetration = r - dist ;
            glm::vec2 correction = normalVector * penetration * 0.5f ;

            glm::vec2 vi = balls[i].cur_pos - balls[i].prev_pos ;
            glm::vec2 vj = balls[j].cur_pos - balls[j].prev_pos ;
            glm::vec2 vrel = vj - vi ;

            float approachingSpeed = glm::dot(vrel , normalVector) ;
            float bounce = 0.0f ;
            if(approachingSpeed < 0.0f) bounce = -approachingSpeed * restitution ;

            glm::vec2 restitutionCorrection = normalVector * bounce * 0.5f ;

            balls[i].cur_pos -= correction + restitutionCorrection ;
            balls[j].cur_pos += correction + restitutionCorrection ;

            /*glm::vec2 dispi = balls[i].cur_pos - balls[i].prev_pos ;
            glm::vec2 dispj = balls[j].cur_pos - balls[j].prev_pos ;

            glm::vec2 disprel = dispj - dispi ;
            float relNormal = glm::dot(disprel , normalVector) ;
            if(relNormal > 0.0f) continue ; 
            float impulseMag = -(1.0f + restitution) * relNormal * 0.5f ;
            glm::vec2 impulse = impulseMag * normalVector ;

            dispi -= impulse ;
            dispj += impulse ;

            disprel = dispj - dispi ;
            glm::vec2 tangentVector = disprel - normalVector * relNormal ;
            if(glm::length(tangentVector) > 0.0001f) {
                tangentVector = glm::normalize(tangentVector) ;
                glm::vec2 frictionImpulse = tangentVector * friction * glm::length(impulse) ;

                dispi -= frictionImpulse ;
                dispj += frictionImpulse ;
            }

            balls[i].prev_pos = balls[i].cur_pos - dispi ;
            balls[j].prev_pos = balls[j].cur_pos - dispj ;*/
        }
    }
}

void System::update(std::vector<Ball>& balls , float dt , glm::vec2& gravity) {
    for(std::vector<Ball>::iterator it = balls.begin() ; it != balls.end() ; ++it) {
        it->integrate(dt , gravity) ;
        it->applyGroundFriction() ;
        for(int i = 0 ; i < constraintIterations ; i++) it->handleWallCollisions() ;
    }
    for(int i = 0 ; i < constraintIterations ; i++) handleBallCollisions(balls) ;
}

void System::resetSimulation(DataReader reader , std::vector<Ball>& balls , std::vector<TrajectoryBuffer>& tb , glm::vec2& gravity , const float initdt , bool* isPlaying) {
    balls.clear() ;
    tb.clear() ;
    reader.readFile(balls , gravity , initdt) ;
    if(*isPlaying == false) *isPlaying = true ;
}