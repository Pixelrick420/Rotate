# SDL Rotating Cube Visualization
![image](https://github.com/user-attachments/assets/a9c809fb-c00c-4127-b27e-86e9da313660)

## Overview
This is a simple C++ application that renders and animates a 3D cube using SDL2 (Simple DirectMedia Layer). The cube rotates continuously around its centroid, demonstrating basic 3D transformation and rendering techniques.This project was done following [this](https://www.youtube.com/watch?v=kdRJgYO1BJM&ab_channel=TheBuilder) tutorial by The Builder.

## Features
- Renders a wireframe cube
- Real-time 3D rotation on multiple axes
- Simple SDL2-based graphics rendering
- Smooth animation loop

## Prerequisites/Dependencies
- SDL2 library
- C++ compiler with C++11 support (g++ recommended)
- CMake or Make for building
- SDL2 development libraries

## How to run
To compile the project, use the following command: <br>
```g++ -I<path to SDL include> -L<path to SDL lib> -o rotateCube rotateCube.cpp -lmingw32 -lSDL2main -lSDL2``` <br>
After compilation, run the executable:<br>
```./rotateCube```<br>

Alternatively, you can download and run the executable on windows using: <br>
```start rotateCube```<br>
The application will automatically start rotating the cube. Close the window to exit the program<br>

## Code Structure
- Vector3 struct for 3D point representation
- Cube struct to manage cube geometry and transformations
- Screen struct for SDL rendering management
- Functions for creating, drawing, and rotating the cube
- Main loop for continuous rendering and rotation

