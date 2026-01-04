# Kinetica
**Kinetica** is a real-time 2D physics simulation engine developed in **C++** using **SDL2**, **OpenGL**, and **ImGui**.The project demonstrates a clean and modular approach to deterministic simulation, interactive visualization, and low-level graphics programming.

At its core, Kinetica implements a fixed timestep physics loop with an accumulator, ensuring stable and reproducible simulation behavior independent of frame rate. The simulation supports dynamic bodies with configurable physical properties and provides fine-grained control over execution through an integrated debugging interface.

## Features
-**Real-time 2D physics simulation** using fixed-timestep integration
- Stable ball–ball and ball–wall collision handling with restitution and friction
-**OpenGL** rendering with motion trajectories and alpha-faded trails
-ImGui-based controls for play/pause, step, reset, gravity, and time scaling

##  Installation And Setup
### Clone The Repository
```bash
git clone https://github.com/YourUsername/kinetica.git
cd kinetica
```

### Install Required Dependencies
Install OpenGL , SDL2 libraries as well as CMake on your specific operating system as per the installation guides for these libraries .

### Build
build the executable on your specific os using cmake commands
```bash
cmake -S . -B build
cmake --build build
```

### Datafile Setup
additionally , **kinetica** requires a datafile located in
```bash
/user-data/datafile.txt
```
Make sure this folder exists **relative to the executable** :
```bash
kinetica/
 ├── build/
 ├── user-data/
 │    └── datafile.txt
```
Instructions on the use of the datafile are provided inside **datafile.txt** along with some examples .

## How To Use 
run the make file in **build** directory which will create a executable .
```bash
./build/kinetica
```

## Tech Stack
- C++ (C++ 17)
- OpenGL
- SDL2
- ImGui
- CMake

