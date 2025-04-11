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


int main() {

    Vec2<double> pos(22, 12);
    Vec2<double> dir(-1, 0);       // looking left
    Vec2<double> plane(0, 0.66);   // camera plane (screen width in world units)

      double time = 0; //time of current frame
      double oldTime = 0; //time of previous frame
      //rendering the window
      SDL_Window* window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      while(!done())
      {
          for (int x = 0; x < screenWidth; x++) {
            double cameraX = 2 * (x / double(screenWidth)) - 1;
            Vec2<double> rayDir = dir + (plane * cameraX);

            //which box of the map we're in
            Vec2<int> mapStep = Vec2<int>(int(pos.x), int(pos.y));

            //length of ray from current position to next x or y-side
            Vec2<double> SideDist;
            //length of ray from one x or y-side to next x or y-side
            //to avoid division by zero if the ray distance is 0 i.e the ray is going exactly horizontal
            //or vertical we assign it a very large value
            Vec2<double> delta = Vec2<double>(
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
                SideDist.x = (pos.x - mapStep.x) * delta.x;
            }
            else {
                Step.x = 1;
                SideDist.x = (mapStep.x + 1.0 - pos.x) * delta.x;
            }
            if(rayDir.y < 0)
            {
                Step.y = -1;
                SideDist.y = (pos.y - mapStep.y) * delta.y;
            }
            else {
                Step.y = 1;
                SideDist.y = (mapStep.y + 1.0 - pos.y) * delta.y;
            }
          }


      }


}
