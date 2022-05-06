#pragma once
#include <SDL2/SDL.h>

#include <vector>

#include "game.h"
#include "entities/movable.h"
#include "entities/sheep.h"
#include "entities/dog.h"

#include "entities/helpers/chunk.h"
#include "entities/helpers/chunkManager.h"

class SheepGame : public Game
{
public:
  SheepGame(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight);

public:
  void init() override;
  bool update() override;
  void render() override;

private:
  void updateSheep();

private:
  std::vector<Movable *> m_sheepList; // Holds all the sheep (objects) in a vector
  std::vector<Movable *> m_dogList;   // Holds all the sheep (objects) in a vector
  std::vector<std::vector<Movable *>> m_sheepGrid;
  const uint32_t m_numSheep = 100; // Num sheep to spawn
  ChunkManager m_chunkManager;
};