struct SDL_Renderer;
#include "../math/vector2.h"

class Renderable
{
public:
  Renderable(){};

public:
  void render(SDL_Renderer *renderer);

  inline Vector2 getPosition() { return m_position; };

protected:
  Vector2 m_position;
};