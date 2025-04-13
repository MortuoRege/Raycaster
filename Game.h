// Game.h
#pragma once
#include <SDL2/SDL.h>
#include "Vec2.h"

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void cleanup();

private:
    void handleInput();
    void update();
    void render();
    bool isRunning;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Vec2<double> pos;
    Vec2<double> dir;
    Vec2<double> plane;

    double moveSpeed;
    double rotSpeed;
};
