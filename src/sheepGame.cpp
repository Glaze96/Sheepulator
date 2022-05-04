#include "sheepGame.h"
#include <iostream>

SheepGame::SheepGame(SDL_Renderer **renderer, uint32_t screenWidth, uint32_t screenHeight) : Game(renderer, screenWidth, screenHeight){};

void SheepGame::init()
{
}

bool SheepGame::update(uint32_t countedFrames)
{
  SDL_PollEvent(&m_event);
  switch (m_event.type)
  {
  case SDL_KEYDOWN:
    if (m_event.key.keysym.sym == SDLK_SPACE) // ON SPACE
    {
      for (auto sheep : sheepList)
        delete sheep;
      sheepList.clear();

      for (auto dog : dogList)
        delete dog;
      dogList.clear();
      
      // GENERATE NEW SHEEPS
      int newSheepAmmout = 100;
      for (int i = 0; i < newSheepAmmout; i++)
      {
        float randX = (rand() % (int)m_screenWidth - 1);
        float randY = (rand() % (int)m_screenHeight - 1);
        // printf("X-RAND: %f, Y-RAND: %f \n",randX, randY);
        Sheep *sheep = new Sheep(randX, randY, 0.5f, sheepList, dogList);
        sheepList.push_back(sheep);
      }
    }

    if (m_event.key.keysym.sym == SDLK_1)
    {
      float randX = (rand() % (int)m_screenWidth - 1);
      float randY = (rand() % (int)m_screenHeight - 1);
      Dog *dog = new Dog(randX, randY, 2.0f, sheepList, dogList);
      dogList.push_back(dog);
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

  for (int i = 0; i < sheepList.size(); i++)
  {

    std::cout << "updating sheep" << std::endl;
    Sheep *sheep = (Sheep *)sheepList.at(i);
    sheep->update(countedFrames);
  }

  for (int i = 0; i < dogList.size(); i++)
  {
    Dog *dog = (Dog *)dogList.at(i);
    dog->update(countedFrames);
  }

  return true;
};

void SheepGame::render()
{
  // Sets sheep color
  SDL_SetRenderDrawColor(*m_renderer, 255, 255, 255, 255);

  // Main loop for sheep updates
  for (int i = 0; i < sheepList.size(); i++)
  {
    // std::cout << "rendering sheep" << std::endl;
    Sheep *sheep = (Sheep *)sheepList.at(i);
    sheep->render(*m_renderer);
  }

  SDL_SetRenderDrawColor(*m_renderer, 255, 0, 0, 255);
  for (int i = 0; i < dogList.size(); i++)
  {
    Dog *dog = (Dog *)dogList.at(i);
    dog->render(*m_renderer);
  }
};