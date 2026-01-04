#pragma once
#include <vector>
#include "ball.h"

#define MAX_TRAJ_POS 50

struct TrajectoryPoint {
    float x , y ;
} ;

struct TrajectoryBuffer {
    TrajectoryPoint points[MAX_TRAJ_POS] ;
    int head , count ;
} ;

class Trajectory {
public:
    std::vector<TrajectoryBuffer> initTrajectoryBufferGL(std::vector<Ball>& balls) ;
    void AddTrajectoryPoints(std::vector<TrajectoryBuffer>& tb , std::vector<Ball>& balls) ;
    void DrawTrajectoryGL(std::vector<TrajectoryBuffer>& tb , std::vector<Ball>& balls) ;
} ;