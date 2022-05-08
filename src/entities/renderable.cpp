#include "renderable.h"
#include <SDL2/SDL.h>
#include <stdio.h>

Renderable::Renderable(float startX, float startY) {
  Renderable(Vector2(startX, startY));
}

Renderable::Renderable(const Vector2 &startPos) {
  m_position = startPos;
}

void Renderable::render(SDL_Renderer *renderer)
{
  SDL_RenderDrawPoint(renderer, int(m_position.X), int(m_position.Y));
}