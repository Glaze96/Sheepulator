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

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

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

  srand(time(NULL));

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
  int countedFrames = 0;
  fpsTimer.start();

  float sineOffset = 0.0f;

  std::vector<Sheep> sheepList;

  for (int i = 0; i < 20000; i++) {
    float randX = rand() % SCREEN_WIDTH - 1;
    float randY = rand() % SCREEN_HEIGHT - 1;
    sheepList.push_back(Sheep(randX, randY));
  }

  while (1)
  {
    capTimer.start();

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;

    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (avgFPS > 2000000)
      avgFPS = 0;

    std::cout << "Average FPS: " << avgFPS << "\n";

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    for (auto &sheep : sheepList) {
      sheep.move(rand() % 11 - 5,  rand() % 11 - 5);
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