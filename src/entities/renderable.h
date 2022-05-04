struct SDL_Renderer;
#include "../math/vector2.h"
#include "../settings.h"

class Renderable
{
public:
  void render(SDL_Renderer *renderer);

  inline Vector2 getPosition() const { return m_position; };
  inline void setPosition(float x, float y)
  {
    if (x < 0)
      x = 0;

    if (x > Settings::SCREEN_WIDTH - 1)
      x = Settings::SCREEN_WIDTH - 1;

    if (y < 0)
      y = 0;

    if (y > Settings::SCREEN_HEIGHT - 1)
      y = Settings::SCREEN_HEIGHT - 1;

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