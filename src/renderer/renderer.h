#pragma once
#include <glm/glm.hpp>
#include "physics/ball.h"

class Renderer {
public:
    void Init(int width , int height) ;
    void BeginFrame() ;
    void DrawCircle(const glm::vec2& pos , const float radius , struct rgbaColor& color) ;
};