#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

#include "src/math/LTimer.h"
#include "src/sheepGame.h"

#include "src/settings.h"
#include "src/input/inputManager.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char *args[])
{
  // The window we'll be rendering to
  SDL_Window *window = NULL;

  SDL_Renderer *renderer;

  SheepGame game(&renderer, Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);

  srand(time(NULL)); // random seed

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  // Create window
  SDL_CreateWindowAndRenderer(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, 0, &window, &renderer);

  LTimer fpsTimer;
  LTimer capTimer;

  uint32_t countedFrames = 0;
  fpsTimer.start();

  bool running = true; // check if we want to quit

  game.init();

  while (running) // main program loop
  {
    InputManager::getInstance()->update();
    capTimer.start();

    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (countedFrames % 60 == 0)
      std::cout << "Average FPS: " << avgFPS << "\n";

    running = game.update(countedFrames);
    // Clear window to black
    SDL_SetRenderDrawColor(renderer, 5, 50, 10, 255);
    SDL_RenderClear(renderer);

    game.render();

    // Show render
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
  return 0;
}