#include "renderable.h"
#include <SDL2/SDL.h>

void Renderable::render(SDL_Renderer *renderer)
{
  SDL_RenderDrawPoint(renderer, m_x, m_y);
}

void Renderable::setPosition(float x, float y)
{
  m_x = x;
  m_y = y;
}