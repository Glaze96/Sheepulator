struct SDL_Renderer;
#include "../math/vector2.h"
#include "../settings.h"
#include <algorithm>

class Renderable
{
public:
  void render(SDL_Renderer *renderer);

  inline Vector2 getPosition() const { return m_position; };
  inline void setPosition(float x, float y)
  {
    x = std::clamp((int)x, 0, (int)Settings::SCREEN_WIDTH - 1);
    y = std::clamp((int)y, 0, (int)Settings::SCREEN_HEIGHT - 1);

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