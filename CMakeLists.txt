cmake_minimum_required(VERSION 3.10)

project(kinetica LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(kinetica
    src/main.cpp
    src/app/app.cpp
    src/physics/ball.cpp
    src/physics/system.cpp
    src/physics/trajectory.cpp
    src/renderer/renderer.cpp
    src/data-reader/data-reader.cpp
    src/user-interface/ui.cpp

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(kinetica PRIVATE
    src
    external/imgui
    external/imgui/backends
)

target_link_libraries(kinetica PRIVATE
    SDL2::SDL2
    OpenGL::GL
)

