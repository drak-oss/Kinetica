#include "trajectory.h"
#include <SDL2/SDL_opengl.h>

std::vector<TrajectoryBuffer> Trajectory::initTrajectoryBufferGL(std::vector<Ball>& balls) {
    glDisable(GL_TEXTURE_2D) ;
    glDisable(GL_LIGHTING) ;
    glEnable(GL_BLEND) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glLineWidth(1.5f) ;
    int trajSize = balls.size() ;
    std::vector<TrajectoryBuffer> trajHeads ;
    for(int i = 0 ; i < trajSize ; i++) {
        TrajectoryBuffer tb ;
        tb.head = 0 , tb.count = 0 ;
        
        tb.points[0] = {balls[i].cur_pos.x , balls[i].cur_pos.y} ;
        tb.count++ ;
        tb.head = (tb.head + 1) % MAX_TRAJ_POS ;
        trajHeads.push_back(tb) ;
    }
    return trajHeads ;
}

void Trajectory::AddTrajectoryPoints(std::vector<TrajectoryBuffer>& tb , std::vector<Ball>& balls) {
    int trajSize = balls.size() ;
    for(int i = 0 ; i < trajSize ; i++) {
        tb[i].points[tb[i].head] = {balls[i].cur_pos.x , balls[i].cur_pos.y} ;
        tb[i].head = (tb[i].head + 1) % MAX_TRAJ_POS ;
        if(tb[i].count < MAX_TRAJ_POS) tb[i].count++ ;
    }
}

void Trajectory::DrawTrajectoryGL(std::vector<TrajectoryBuffer>& tb , std::vector<Ball>& balls) {
    int trajSize = balls.size() ;
    for(int i = 0 ; i < trajSize ; i++) {
        if(tb[i].count <= 2) continue ;

        glBegin(GL_LINE_STRIP) ;
        int start = (tb[i].head - tb[i].count + MAX_TRAJ_POS) % MAX_TRAJ_POS ;
        for(int j = 0 ; j < tb[i].count ; j++) {
            int idx = (start + j) % MAX_TRAJ_POS ;
            float x = tb[i].points[idx].x ;
            float y = tb[i].points[idx].y ;

            int minAlpha = 20 , maxAlpha = 255 ;
            float t = (float)j / (tb[i].count - 1) ;
            float alpha = (minAlpha + t * (maxAlpha - minAlpha)) / 255.0f ;
            glColor4f(balls[i].color.r , balls[i].color.g , balls[i].color.b , alpha) ;
 
            glVertex2f(x , y) ;
        }
        glEnd() ;
    }
}