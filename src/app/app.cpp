#include "app.h"

#define WIDTH 1280
#define HEIGHT 720

static glm::vec2 gravity = {0.0f , 1200.0f} ;
static const float initdt = 0.016f ;

bool App::initApp() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false ;

    window = SDL_CreateWindow("Bouncing Balls" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , SDL_WINDOW_OPENGL) ;
    glContext = SDL_GL_CreateContext(window) ;
    if(glContext == nullptr) return false ;

    renderer.Init(WIDTH , HEIGHT) ;

    std::string path = reader.getExecutableDir() ;
    reader.filePath = path + "/../user-data/datafile.txt" ;
    if(reader.readFile(balls , gravity , initdt) == false) return false ;
    trajHeads = traj.initTrajectoryBufferGL(balls) ;
    ui.initUI(window , glContext) ;
    return true ;
}

void App::runApp() {
    bool running = true ;
    float accumulator = 0.0f ;
    const float fixedDT = 1.0f / 120.0f ;
    Uint32 lastTicks = SDL_GetTicks() ;

    while(running) {
        SDL_Event event ;
        while(SDL_PollEvent(&event)) {
            ui.hookUIControls(&event) ;
            if(event.type == SDL_QUIT) running = false ;
            else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) running = false ;
            }
            else if(event.type == SDL_WINDOWEVENT_CLOSE) {
                if(window != NULL) {
                    SDL_DestroyWindow(window) ;
                    window = NULL ;
                }
            }
        }

        Uint32 curTicks = SDL_GetTicks() ;
        float rawDT = (curTicks - lastTicks) / 1000.0f ;
        lastTicks = curTicks ;

        if(rawDT > 0.016f) rawDT = 0.016f ;
        if(rawDT <= 0.0f) continue ;

        if(simsets.isPlaying) accumulator += rawDT * simsets.timeScale ;
        if(simsets.stepOnce) accumulator += fixedDT; 

        if(ui.resetSim) {
            system.resetSimulation(reader , balls , trajHeads , gravity , initdt , &simsets.isPlaying) ;
            ui.resetSim = false ;
        }

        traj.AddTrajectoryPoints(trajHeads , balls) ;

        while(accumulator >= fixedDT) {
            system.update(balls , fixedDT , gravity) ;
            accumulator -= fixedDT ;

            if (simsets.stepOnce) {
                simsets.stepOnce = false ;
                simsets.isPlaying = false ;
                accumulator = 0.0f ;
                break ;
            }
        }

        float fps = 1/fixedDT ;
        int ballCount = balls.size() ;

        renderer.BeginFrame() ;
        if(simsets.showTraj) traj.DrawTrajectoryGL(trajHeads , balls) ;
        ui.renderUI(fps , ballCount , &simsets.isPlaying , &simsets.stepOnce , &ui.resetSim , &gravity.y , &simsets.timeScale , &simsets.showTraj) ;
        for(std::vector<Ball>::iterator it = balls.begin() ; it != balls.end() ; ++it) renderer.DrawCircle(it->cur_pos , it->radius , it->color) ;
        SDL_GL_SwapWindow(window) ;
    }
}

void App::shutdownApp() {
    ui.shutdownUI() ;
    SDL_GL_DeleteContext(glContext) ;
    SDL_DestroyWindow(window) ;
    SDL_Quit() ;
}