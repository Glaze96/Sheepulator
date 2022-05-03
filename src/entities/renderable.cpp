#include "renderable.h"
#include <SDL2/SDL.h>
#include <stdio.h>

void Renderable::render(SDL_Renderer *renderer)
{
  SDL_RenderDrawPoint(renderer, int(m_position.X), int(m_position.Y));
}