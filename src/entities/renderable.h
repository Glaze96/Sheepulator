struct SDL_Renderer;
#include "../math/vector2.h"

class Renderable
{
public:
  Renderable() {};

public:
  void render(SDL_Renderer *renderer);

public:
  void setPosition(const Vector2 &position);

  // Position (in screen space 'currently')
protected:
  Vector2 m_position;
};