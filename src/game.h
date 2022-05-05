#pragma once
#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

class Game
{
public:
  Game(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight);
  virtual ~Game();

public:
  virtual void init(){};
  virtual bool update(float frameTime)
  {
    std::cout << "Override update please!!" << std::endl;
    return false;
  };
  virtual void render(){};

protected:
  SDL_Event m_event;
  SDL_Renderer **m_renderer;
  uint32_t m_screenWidth;
  uint32_t m_screenHeight;
  bool m_running;
};