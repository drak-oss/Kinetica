#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "physics/ball.h"
#include "renderer/renderer.h"
#include "data-reader/data-reader.h"
#include "physics/system.h"
#include "user-interface/ui.h"
#include "physics/trajectory.h"

struct SimulationSettings {
    float timeScale = 1.0f ;
    bool isPlaying = true ;
    bool stepOnce = false ;
    bool showTraj = false ;
} ;

class App {
public :
    bool initApp() ;
    void runApp() ;
    void shutdownApp() ;

private:
    SDL_Window* window = nullptr ;
    SDL_GLContext glContext ;

    SimulationSettings simsets ;
    Renderer renderer ;
    std::vector<Ball> balls ;
    System system ;
    DataReader reader ;
    UserInterface ui ;
    Trajectory traj ;
    std::vector<TrajectoryBuffer> trajHeads ;
} ;