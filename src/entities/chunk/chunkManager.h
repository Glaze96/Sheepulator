#pragma once
#include "chunk.h"
#include <vector>

class ChunkManager {
public:
  ChunkManager();
  
  void generateChunks(int totalWidth, int totalHeight, int chunkWidth);

  Chunk getChunkFromPosition(const Vector2 &position);
  // std::vector<Chunk *> getSurroundingChunks(Chunk *chunk);
  std::vector<Movable *> getMovablesInChunk(Chunk *chunk);

  // Always update chunks
  void updateChunks(const std::vector<Movable *> &movabales);

private:

private:
  int m_numChunksX, m_numChunksY;
  int m_chunkWidth;
  std::vector<Chunk> m_chunks;
};