#include "singletons.h"

Renderer* sRenderer = NULL;
Input* sInput = NULL;
ResourceManager* sResManager = NULL;
SceneDirector* sDirector = NULL;
SoundManager* sSoundManager = NULL;

void initSingletons() {
	sRenderer = Renderer::getInstance();
	sInput = Input::getInstance();
	sResManager = ResourceManager::getInstance();
	sDirector = SceneDirector::getInstance();
	sSoundManager = SoundManager::getInstance();

	sRenderer->setFramerate(60);
	sInput->setWindow(sRenderer->getWindow());
}
