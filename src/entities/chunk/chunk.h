#pragma once
#include <vector>
#include "../movable.h"

class Chunk
{
public:
  Chunk(int chunkPosX, int chunkPosY, int width);

public:
  bool isInChunk(Movable *movable);
  void addToChunk(Movable *movable);
  void clearChunk();
  std::vector<Movable *> getMovables();
  
private:
  int m_worldPosX, m_worldPosY;
  int m_chunkPosX, m_chunkPosY;
  int m_width;
  std::vector<Movable *> m_movables;
};