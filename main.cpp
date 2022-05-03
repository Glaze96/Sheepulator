#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

#include "src/LTimer.h"
#include "src/entities/sheep.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char *args[])
{
  SDL_Event event;

  // The window we'll be rendering to
  SDL_Window *window = NULL;

  // The surface contained by the window
  SDL_Surface *screenSurface = NULL;

  SDL_Renderer *renderer;

  srand(time(NULL)); // random seed

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
  // Create window
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

  LTimer fpsTimer;
  LTimer capTimer;

  uint32_t countedFrames = 0;
  fpsTimer.start();

  std::vector<Sheep> sheepList; // Holds all the sheep (objects) in a vector
  
  bool running = true; // check if we want to quit

  while (running) // main program loop
  {
    capTimer.start();

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE) // ON SPACE
        {
          sheepList.clear();

          // GENERATE NEW SHEEPS
          int newSheepAmmout = 10000;
          for (int i = 0; i < newSheepAmmout; i++) 
          {
            float randX = (rand() % (int)SCREEN_WIDTH - 1);
            float randY = (rand() % (int)SCREEN_HEIGHT - 1);
            // printf("X-RAND: %f, Y-RAND: %f \n",randX, randY);
            Sheep sheep = Sheep(randX, randY, 1.f);
            sheepList.push_back(sheep);
          }
          // Init sheeps in sheeps list
          //  ---  Could maybe be baked into generation?
          for (int i = 0; i < newSheepAmmout; i++)
          {
            sheepList[i].init(&sheepList);
          }
        }

        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }

        printf("Key press detected\n");
        break;

      case SDL_KEYUP:
        printf("Key release detected\n");
        break;

      case SDL_QUIT:
        running = false;
        break;

      default:
        break;
      }
    }

    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (countedFrames % 60 == 0)
      std::cout << "Average FPS: " << avgFPS << "\n";

    // Clear window to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);


    // Sets sheep color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Main loop for sheep updates
    for (auto &sheep : sheepList)
    {
      sheep.update(countedFrames);
      sheep.render(renderer);
    }


    SDL_RenderPresent(renderer);

    ++countedFrames;

    int frameTicks = capTimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME)
    {
      // Wait remaining time
      SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
  }

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();
  printf("IT ACTUALLY WORKS! TRUST ME!");
  return 0;
}