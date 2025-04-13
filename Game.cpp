#include "Game.h"
#include <cmath>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


Game::Game()
    : window(nullptr), renderer(nullptr),
      pos(22.0, 12.0), dir(-1.0, 0.0), plane(0.0, 0.66),
      moveSpeed(0.01), rotSpeed(0.001), isRunning(true)
{}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer != nullptr;
}

void Game::run() {
    while (isRunning) {
        handleInput();
        update();
        render();
    }
}
void Game::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            isRunning = false;
    }
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_UP]) {
            if (worldMap[int(pos.x + dir.x * moveSpeed)][int(pos.y)] == 0)
                pos.x += dir.x * moveSpeed;
            if (worldMap[int(pos.x)][int(pos.y + dir.y * moveSpeed)] == 0)
                pos.y += dir.y * moveSpeed;
        }

        if (keystate[SDL_SCANCODE_DOWN]) {
            if (worldMap[int(pos.x - dir.x * moveSpeed)][int(pos.y)] == 0)
                pos.x -= dir.x * moveSpeed;
            if (worldMap[int(pos.x)][int(pos.y - dir.y * moveSpeed)] == 0)
                pos.y -= dir.y * moveSpeed;
        }

        if (keystate[SDL_SCANCODE_RIGHT]) {
            dir = dir.rotated(-rotSpeed);
            plane = plane.rotated(-rotSpeed);
        }

        if (keystate[SDL_SCANCODE_LEFT]) {
            dir = dir.rotated(rotSpeed);
            plane = plane.rotated(rotSpeed);
        }

}
void Game::update() {
    // Currently unused; could later use for delta time, AI, etc.
}

void Game::render() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(renderer);
    for (int x = 0; x < screenWidth; x++) {
      double cameraX = 2 * (x / double(screenWidth)) - 1;
      Vec2<double> rayDir = dir + (plane * cameraX);

      //which box of the map we're in
      Vec2<int> map= Vec2<int>(int(pos.x), int(pos.y));

      //length of ray from current position to next x or y-side
      Vec2<double> SideDist;
      //length of ray from one x or y-side to next x or y-side
      //to avoid division by zero if the ray distance is 0 i.e the ray is going exactly horizontal
      //or vertical I assigned it a very large value
      Vec2<double> deltaDist = Vec2<double>(
            rayDir.x == 0 ? 1e30  : abs(1 / rayDir.x),
            rayDir.y == 0 ? 1e30  : abs(1 / rayDir.y)
        );
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      Vec2<int> Step;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      if(rayDir.x < 0)
      {
          Step.x = -1;
          SideDist.x = (pos.x - map.x) * deltaDist.x;
      }
      else {
          Step.x = 1;
          SideDist.x = (map.x + 1.0 - pos.x) * deltaDist.x;
      }
      if(rayDir.y < 0)
      {
          Step.y = -1;
          SideDist.y = (pos.y - map.y) * deltaDist.y;
      }
      else {
          Step.y = 1;
          SideDist.y = (map.y + 1.0 - pos.y) * deltaDist.y;
      }
      while (hit == 0)
            {
              //jump to next map square, either in x-direction, or in y-direction
              if (SideDist.x < SideDist.y)
              {
                SideDist.x += deltaDist.x;
                map.x += Step.x;
                side = 0;
              }
              else
              {
                SideDist.y += deltaDist.y;
                map.y += Step.y;
                side = 1;
              }
              //Check if ray has hit a wall
              if (worldMap[map.x][map.y] > 0) hit = 1;
            }
            if(side == 0){
            perpWallDist = (SideDist.x - deltaDist.x);
            }
            else {
                perpWallDist = (SideDist.y - deltaDist.y);
            }

            int lineHeight = (int)(screenHeight / perpWallDist);
                    int drawStart = -lineHeight / 2 + screenHeight / 2;
                    if (drawStart < 0) drawStart = 0;
                    int drawEnd = lineHeight / 2 + screenHeight / 2;
                    if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

                    if (side == 0)
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
                    else
                        SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255); // dark red

                    SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }

    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
