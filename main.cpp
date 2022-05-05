#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>

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

  fpsTimer.start();

  bool running = true; // check if we want to quit

  game.init();

  std::chrono::duration<double> elapsed;

  float secondCounter = 0;
  float lastFrameTime = 1.0f/ SCREEN_FPS;

  while (running) // main program loop
  {
    auto start = std::chrono::high_resolution_clock::now();
    capTimer.start();


    InputManager::getInstance()->update();

    running = game.update(lastFrameTime);
    
    // Clear window to black
    SDL_SetRenderDrawColor(renderer, 5, 50, 10, 255);
    SDL_RenderClear(renderer);

    game.render();

    // Show render
    SDL_RenderPresent(renderer);

    int frameTicks = capTimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME)
    {
      // Wait remaining time
      SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }

    auto finish = std::chrono::high_resolution_clock::now();

    elapsed = finish - start;
    lastFrameTime = elapsed.count();
    secondCounter += elapsed.count();

    // Happens EVERY one second
    if (secondCounter > 1.0f)
    {
      std::cout << "FPS: " << (int)(1.0f / elapsed.count()) << std::endl;
      secondCounter = 0.0f;
    }

  }

  // Destroy window
  SDL_DestroyWindow(window);
  // Quit SDL subsystems
  SDL_Quit();
  return 0;
}