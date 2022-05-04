#include "inputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::getInstance()
{
	if (!instance)
		instance = new InputManager();

	return instance;
}