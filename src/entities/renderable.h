struct SDL_Renderer;
#include "../math/vector2.h"

class Renderable
{
public:
  Renderable() {};

public:
  void render(SDL_Renderer *renderer);

protected:
  Vector2 m_position;
};