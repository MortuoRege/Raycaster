**Raycaster Engine**

A simple raycasting engine built from scratch using C++ and SDL2, inspired by the rendering techniques of early 3D games like Wolfenstein 3D. This project is designed to help understand the fundamentals of real-time 3D rendering and grid-based world navigation.

**Main Principle**
The engine uses the Digital Differential Analyzer (DDA) algorithm for raycasting. If we imagine the world as a grid with 1x1 cells, the algorithm doesn’t increment the ray gradually with small steps. Instead, it efficiently steps from one grid cell ("box") to the next, following the ray’s path, until it hits an obstacle.
