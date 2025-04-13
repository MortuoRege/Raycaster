#include <iostream>
#include <SDL2/SDL.h>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#include "Vec2.h"

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

//this code is here for the game loop
bool done() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}
bool keyDown(SDL_Scancode scancode) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[scancode];
}


int main() {

    Vec2<double> pos(22, 12);      //players position in the world
    Vec2<double> dir(-1, 0);       // player is looking left looking left
    Vec2<double> plane(0, 0.66);   // camera plane (screen width in world units)
      //rendering the window
      SDL_Window* window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      while(!done())
      {
          double moveSpeed = 0.01;
          double rotSpeed = 0.001;
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
          // Forward
          if (keyDown(SDL_SCANCODE_UP)) {
              if (worldMap[int(pos.x + dir.x * moveSpeed)][int(pos.y)] == 0)
                  pos.x += dir.x * moveSpeed;
              if (worldMap[int(pos.x)][int(pos.y + dir.y * moveSpeed)] == 0)
                  pos.y += dir.y * moveSpeed;
          }

          // Backward
          if (keyDown(SDL_SCANCODE_DOWN)) {
              if (worldMap[int(pos.x - dir.x * moveSpeed)][int(pos.y)] == 0)
                  pos.x -= dir.x * moveSpeed;
              if (worldMap[int(pos.x)][int(pos.y - dir.y * moveSpeed)] == 0)
                  pos.y -= dir.y * moveSpeed;
          }
          if (keyDown(SDL_SCANCODE_RIGHT)) {
              dir = dir.rotated(-rotSpeed);
              plane = plane.rotated(-rotSpeed);
          }
          if (keyDown(SDL_SCANCODE_LEFT)) {
              dir = dir.rotated(rotSpeed);
              plane = plane.rotated(rotSpeed);
          }



          SDL_RenderPresent(renderer);

      }


}
