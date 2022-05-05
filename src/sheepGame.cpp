#include "sheepGame.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "input/inputManager.h"

SheepGame::SheepGame(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight) : Game(renderer, screenWidth, screenHeight){};

void SheepGame::init()
{
  std::cout << "1 to add 'x amount' SHEEP" << std::endl;
  std::cout << "2 to add one DOG" << std::endl;
  std::cout << "0 to add one SHEEP" << std::endl;
  std::cout << "SPACE clear all" << std::endl;
  std::cout << "RETURN for debug logs" << std::endl;

  for (int y = 0; y < m_screenHeight; y++)
  {
    std::vector<Movable *> row;
    for (int x = 0; x < m_screenWidth; x++)
    {
      row.push_back(nullptr);
    }
    m_sheepGrid.push_back(row);
  }

  std::cout << "Y: " << m_sheepGrid.size() << ", X: " << m_sheepGrid[0].size() << std::endl;
}

bool SheepGame::update(uint32_t countedFrames)
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
      float randX = (rand() % (int)m_screenWidth);
      float randY = (rand() % (int)m_screenHeight);
      Sheep *sheep = new Sheep(randX, randY, 0.5f, 20, &m_sheepList, &m_dogList, m_sheepGrid);
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
    float randX = (rand() % (int)m_screenWidth - 1);
    float randY = (rand() % (int)m_screenHeight - 1);
    Dog *dog = new Dog(randX, randY, 0.8f, m_sheepList, m_dogList);
    m_dogList.push_back(dog);
  }

  if (input->isKeyDown(SDL_SCANCODE_RETURN))
  {
    int counter = 0;
    for (int x = 0; x < m_sheepGrid.size() - 1; x++)
    {
      for (int y = 0; y < m_sheepGrid[0].size() - 1; y++)
      {
        if (m_sheepGrid[x][y] != nullptr)
        {
          counter++;
        }
      }
    }
    std::cout << "Num sheep: " << m_sheepList.size() << std::endl;
    std::cout << "Num sheep on grid: " << counter << std::endl;
  }

  // Spawn one sheep center
  if (input->isKeyDown(SDL_SCANCODE_0))
  {
    float randX = Settings::SCREEN_WIDTH / 2;
    float randY = Settings::SCREEN_HEIGHT / 2;
    Sheep *sheep = new Sheep(randX, randY, 0.5f, 20, &m_sheepList, &m_dogList, m_sheepGrid);
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

  // Spawn dog at mouse pos
  if (input->isMouseDown(MouseButton::MOUSE_LEFT))
  {
    int mouseX = input->getMouseX();
    int mouseY = input->getMouseY();
    Dog *dog = new Dog(mouseX, mouseY, 0.8f, m_sheepList, m_dogList);
    m_dogList.push_back(dog);
  }

  updateSheep(countedFrames);

  // Update dogs
  for (int i = 0; i < m_dogList.size(); i++)
  {
    Dog *dog = (Dog *)m_dogList.at(i);
    dog->update(countedFrames);
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
 * sheep->update(cF);
 *
 */

void SheepGame::updateSheep(uint32_t countedFrames)
{
  for (int i = 0; i < m_sheepList.size(); i++)
  {
    Sheep *sheep = (Sheep *)m_sheepList.at(i);

    sheep->update(countedFrames); // update sheep will also update sheep instances pos in grid.
  }
}