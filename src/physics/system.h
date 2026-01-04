#pragma once
#include <vector>
#include "physics/ball.h"
#include "data-reader/data-reader.h"
#include "physics/trajectory.h"

class System {
public:
    void update(std::vector<Ball>& balls , float dt , glm::vec2& gravity) ;
    void resetSimulation(DataReader reader , std::vector<Ball>& balls , std::vector<TrajectoryBuffer>& tb , glm::vec2& gravity , const float initdt , bool* isPlaying) ;

private:
    void handleBallCollisions(std::vector<Ball>& balls) ;
};