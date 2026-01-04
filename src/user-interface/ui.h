#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL2/SDL.h>

class UserInterface {
public:
    bool resetSim = false ;

    void initUI(SDL_Window* window , SDL_GLContext glContext) ;
    void hookUIControls(SDL_Event* event) ;
    void renderUI(float fps, int ballCount, bool * isPlaying, bool * stepOnce, bool * resetSim, float * gravity, float * timeScale , bool* showTraj) ;
    void shutdownUI() ;
} ;