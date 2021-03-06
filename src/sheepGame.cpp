#include "sheepGame.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "input/inputManager.h"
#include <math.h>
#include "settings.h"

SheepGame::SheepGame(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight) : Game(renderer, screenWidth, screenHeight), m_playArea(Vector2(screenWidth, screenHeight)){};

void SheepGame::init()
{
  std::cout << "1 to add 'x amount' SHEEP" << std::endl;
  std::cout << "2 to add one DOG" << std::endl;
  std::cout << "0 to add one SHEEP" << std::endl;
  std::cout << "SPACE clear all" << std::endl;
  std::cout << "RETURN for debug logs" << std::endl;

  std::cout << "LEFT MOUSE CLICK TO SPAWN SHEEP" << std::endl;
  std::cout << "RIGHT MOUSE CLICK TO SPAWN DOG" << std::endl;

  m_chunkManager.generateChunks(m_screenWidth, m_screenHeight, 64);
}

bool SheepGame::update()
{

  InputManager *input = InputManager::getInstance();

  if (input->isKeyDown(SDL_SCANCODE_SPACE))
  {
    for (auto sheep : m_sheepList)
      delete sheep;
    m_sheepList.clear();

    for (auto dog : m_dogList)
      delete dog;
    m_dogList.clear();
  }

  // Spawn 'x' amount of sheep at random positions when pressing 2 key
  if (input->isKeyDown(SDL_SCANCODE_1))
  {
    // GENERATE NEW SHEEPS
    for (int i = 0; i < m_numSheep; i++)
    {
      Sheep *sheep = getSheep();
      m_sheepList.push_back(sheep);
    }

    // INIT NEW SHEEP
    for (int i = 0; i < m_numSheep; i++)
    {
      ((Sheep *)m_sheepList[i])->init();
    }
  }

  // Spawn dog at random position when pressing 2 key
  if (input->isKeyDown(SDL_SCANCODE_2))
  {
    Dog *dog = getDog();
    m_dogList.push_back(dog);
  }

  if (input->isKeyDown(SDL_SCANCODE_RETURN))
  {
    std::cout << "Num sheep: " << m_sheepList.size() << std::endl;
  }

  // Spawn one sheep center
  if (input->isKeyDown(SDL_SCANCODE_0))
  {
    Sheep *sheep = getSheep();
    m_sheepList.push_back(sheep);
    sheep->init();
  }

  // Quit if pressing ESCAPE key
  if (input->isKeyDown(SDL_SCANCODE_ESCAPE))
  {
    return false;
  }

  // if we press the X button
  if (input->quitRequested())
  {
    return false;
  }

  // Spawn sheep at point
  if (input->isMouseDown(MouseButton::MOUSE_LEFT))
  {
    int mouseX = input->getMouseX();
    int mouseY = input->getMouseY();

    for (int i = 0; i < 100; i++)
    {
      int randomX = (rand() % 100) - 50;
      int randomY = (rand() % 100) - 50;
      float randAngle = ((rand() % 10000 / 10000.0f) * M_PI * 2.0f);
      m_sheepList.push_back(getSheep(mouseX, mouseY));
    }
  }

  // Spawn dog at mouse pos
  if (input->isMouseDown(MouseButton::MOUSE_RIGHT))
  {
    int mouseX = input->getMouseX();
    int mouseY = input->getMouseY();
    Dog *dog = getDog(mouseX, mouseY);
    m_dogList.push_back(dog);
  }

  m_chunkManager.updateChunks(m_sheepList);
  updateSheep();

  // Update dogs
  for (int i = 0; i < m_dogList.size(); i++)
  {
    Dog *dog = (Dog *)m_dogList.at(i);
    dog->update();
  }

  // Keep looping
  return true;
};

// RENDER FUNC
void SheepGame::render()
{
  // Sets sheep color
  SDL_SetRenderDrawColor(*m_renderer, 255, 255, 255, 255);
  // Main loop for sheep render
  for (int i = 0; i < m_sheepList.size(); i++)
  {
    // Render sheep
    ((Sheep *)m_sheepList.at(i))->render(*m_renderer);
  }

  // Main loop for dog render
  SDL_SetRenderDrawColor(*m_renderer, 255, 0, 0, 255);
  for (int i = 0; i < m_dogList.size(); i++)
  {
    // Render dog
    ((Dog *)m_dogList.at(i))->render(*m_renderer);
  }
};

/*
 *
 * Sheep update:
 *
 * for each sheep do:
 * sheep->update(frametime);
 *
 */

void SheepGame::updateSheep()
{
  for (int i = 0; i < m_sheepList.size(); i++)
  {
    Sheep *sheep = (Sheep *)m_sheepList.at(i);

    sheep->update(); // update sheep will also update sheep instances pos in grid.
  }
}

Sheep *SheepGame::getSheep(float x, float y)
{
  float randX = x;
  float randY = y;
  if (x < 0 || y < 0)
  {
    randX = (rand() % (int)m_screenWidth - 1);
    randY = (rand() % (int)m_screenHeight - 1);
  }
  float randAngle = ((rand() % 10000 / 10000.0f) * M_PI * 2.0f);
  return new Sheep(Vector2(randX, randY), m_playArea, 0.15f, randAngle, 0.015f, 80, m_chunkManager, m_sheepList, m_dogList);
}

Dog *SheepGame::getDog(float x, float y)
{
  float randX = x;
  float randY = y;
  if (x < 0 || y < 0)
  {
    randX = (rand() % (int)m_screenWidth - 1);
    randY = (rand() % (int)m_screenHeight - 1);
  }
  float randAngle = ((rand() % 10000 / 10000.0f) * M_PI * 2.0f);
  return new Dog(Vector2(randX, randY), m_playArea, 0.8f, randAngle, 0.1f, m_chunkManager, m_sheepList, m_dogList);
}