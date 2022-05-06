#pragma once
#include <SDL2/SDL.h>
#include "../math/vector2.h"
#include "../settings.h"
#include <algorithm>

class Renderable
{
public:
  void render(SDL_Renderer *renderer);

  inline Vector2 getPosition() { return m_position; };
  inline void setPosition(float x, float y)
  {
    x = std::clamp(x, 0.0f, (float)Settings::SCREEN_WIDTH - 1.0f);
    y = std::clamp(y, 0.0f, (float)Settings::SCREEN_HEIGHT - 1.0f);

    m_position.X = x;
    m_position.Y = y;
  };

  inline void addPosition(float x, float y)
  {
    setPosition(m_position.X + x, m_position.Y + y);
  };

private:
  Vector2 m_position;
};