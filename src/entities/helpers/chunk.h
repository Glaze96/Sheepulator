#pragma once
#include <vector>
#include "../movable.h"

class Chunk
{
public:
  Chunk(int posX, int posY, int width);

public:
  int PosX;
  int PosY;
  int Width;
  std::vector<Movable *> Movables;
};