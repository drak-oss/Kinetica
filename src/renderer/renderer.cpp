#include "renderer.h"
#include <SDL2/SDL_opengl.h>
#include <cmath>

#define PI 3.141509f

void Renderer::Init(int width , int height) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glViewport(0, 0, width, height) ;
    glOrtho(0 , width , height , 0 , -1 , 1) ;
    glMatrixMode(GL_MODELVIEW) ;
}

void Renderer::BeginFrame() {
    glClearColor(0.1f , 0.1f , 0.1f , 0.1f) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
    glLoadIdentity() ;
}

void Renderer::DrawCircle(const glm::vec2& pos , const float radius , struct rgbaColor& color) {
    glColor4f(color.r , color.g , color.b , color.a) ;
    glBegin(GL_TRIANGLE_FAN) ;
    glVertex2f(pos.x , pos.y) ;

    for(int i = 0 ; i <= 360 ; i++) {
        float angle = i * PI / 180.0f ;
        glVertex2f(pos.x + cos(angle) * radius , pos.y + sin(angle) * radius) ;
    }
    glEnd() ;
}