#include "sheepGame.h"
#include <iostream>

SheepGame::SheepGame(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight) : Game(renderer, screenWidth, screenHeight){};

void SheepGame::init()
{
  std::cout << "1 to add 'x amount' SHEEP" << std::endl;
  std::cout << "2 to add one DOG" << std::endl;
  std::cout << "SPACE clear all" << std::endl;
}

bool SheepGame::update(uint32_t countedFrames)
{
  SDL_PollEvent(&m_event);
  switch (m_event.type)
  {
  case SDL_KEYDOWN:
    if (m_event.key.keysym.sym == SDLK_SPACE) // ON SPACE
    {
      for (auto sheep : m_sheepList)
        delete sheep;
      m_sheepList.clear();

      for (auto dog : m_dogList)
        delete dog;
      m_dogList.clear();
    }

    if (m_event.key.keysym.sym == SDLK_1)
    {
      // GENERATE NEW SHEEPS
      for (int i = 0; i < m_numSheep; i++)
      {
        float randX = (rand() % (int)m_screenWidth - 1);
        float randY = (rand() % (int)m_screenHeight - 1);
        Sheep *sheep = new Sheep(randX, randY, 0.5f, m_sheepList, m_dogList);
        m_sheepList.push_back(sheep);
      }
    }

    if (m_event.key.keysym.sym == SDLK_2)
    {
      float randX = (rand() % (int)m_screenWidth - 1);
      float randY = (rand() % (int)m_screenHeight - 1);
      Dog *dog = new Dog(randX, randY, 2.0f, m_sheepList, m_dogList);
      m_dogList.push_back(dog);
    }

    if (m_event.key.keysym.sym == SDLK_ESCAPE)
      return false;

    printf("Key press detected\n");
    break;

  case SDL_KEYUP:
    printf("Key release detected\n");
    break;

  case SDL_QUIT:
    return false;
    break;

  default:
    break;
  }

  for (int i = 0; i < m_sheepList.size(); i++)
  {
    Sheep *sheep = (Sheep *)m_sheepList.at(i);
    sheep->update(countedFrames);
  }

  for (int i = 0; i < m_dogList.size(); i++)
  {
    Dog *dog = (Dog *)m_dogList.at(i);
    dog->update(countedFrames);
  }

  return true;
};

void SheepGame::render()
{
  // Sets sheep color
  SDL_SetRenderDrawColor(*m_renderer, 255, 255, 255, 255);

  // Main loop for sheep updates
  for (int i = 0; i < m_sheepList.size(); i++)
  {
    // std::cout << "rendering sheep" << std::endl;
    Sheep *sheep = (Sheep *)m_sheepList.at(i);
    sheep->render(*m_renderer);
  }

  SDL_SetRenderDrawColor(*m_renderer, 255, 0, 0, 255);
  for (int i = 0; i < m_dogList.size(); i++)
  {
    Dog *dog = (Dog *)m_dogList.at(i);
    dog->render(*m_renderer);
  }
};