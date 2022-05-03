#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[])
{
  // The window we'll be rendering to
  SDL_Window *window = NULL;

  // The surface contained by the window
  SDL_Surface *screenSurface = NULL;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
  // Create window
  window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);

  // Fill the surface white
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xAA, 0xFF));

  // Update the surface
  SDL_UpdateWindowSurface(window);

  // Wait two seconds
  SDL_Delay(2000);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();
  printf("IT ACTUALLY WORKS! TRUST ME!");
  return 0;
}

// #include <SDL2/SDL.h>
// // SDL2 Hello, World!
// // This should display a white screen for 2 seconds
// // compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// // run with: ./hello_sdl2
// #include <SDL2/SDL.h>
// #include <stdio.h>

// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480

// int main(int argc, char *args[])
// {
//   SDL_Window *window = NULL;
//   SDL_Surface *screenSurface = NULL;
//   if (SDL_Init(SDL_INIT_VIDEO) < 0)
//   {
//     fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
//     return 1;
//   }
//   window = SDL_CreateWindow(
//       "IT IS ACTUALLY WORKING",
//       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//       SCREEN_WIDTH, SCREEN_HEIGHT,
//       SDL_WINDOW_SHOWN);
//   if (window == NULL)
//   {
//     fprintf(stderr, "could not create window: %s\n", SDL_GetError());
//     return 1;
//   }
//   screenSurface = SDL_GetWindowSurface(window);
//   SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

//   bool quitting = false;
//   // Main loop
//   while (!quitting)
//   {
//     // SDL_UpdateWindowSurface(window);
//     quitting = true;
//   }

//   SDL_Delay(4000);
//   SDL_Quit();
//   printf("Quitting");
//   return 0;
// }