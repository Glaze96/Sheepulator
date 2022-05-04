#include "game.h"

Game::Game(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight) : m_renderer(renderer), m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
  m_event = SDL_Event();
}

Game::~Game(){
  
}