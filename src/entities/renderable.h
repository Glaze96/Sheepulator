struct SDL_Renderer;

class Renderable
{
public:
  Renderable() : m_x(0), m_y(0){};

public:
  void render(SDL_Renderer *renderer);

public:
  float getX() { return m_x; };
  float getY() { return m_y; };
  
  void setPosition(float x, float y);

  // Position (in screen space 'currently')
protected:
  float m_x, m_y;
};