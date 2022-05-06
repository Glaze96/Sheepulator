#pragma once
#include <vector>
#include "../movable.h"

class Chunk
{
public:
  Chunk(int posX, int posY, int width);

public:
  bool isInChunk(Movable *movable);
  void addToChunk(Movable *movable);
  void clearChunk();
  std::vector<Movable *> getMovables();
  
private:
  int m_worldPosX;
  int m_worldPosY;
  int m_width;
  std::vector<Movable *> m_movables;
};