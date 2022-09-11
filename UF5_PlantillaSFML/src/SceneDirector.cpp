#include "SceneDirector.h"

#include "SceneMenu.h"
#include "SceneGame.h"
//incluir las escenas que tengamos

SceneDirector* SceneDirector::instance = NULL;
SceneDirector* SceneDirector::getInstance() {
	if (instance == NULL) {
		instance = new SceneDirector();
	}
	return instance;
}

void SceneDirector::initScenes() {
	_Scenes.resize(LAST_NO_USE);

	SceneMenu* scene_menu = new SceneMenu();
	SceneGame* scene_game = new SceneGame();

	_Scenes[MAIN_MENU] = scene_menu;
	_Scenes[GAME] = scene_game;

	for (size_t i = 0; i < LAST_NO_USE; i++) {
		_Scenes[i]->preLoad();
	}

	_CurrentScene = _Scenes[FIRST_SCENE]; //Escena inicial

}

SceneDirector::SceneDirector() {
	if (instance != NULL) { return; }
	initScenes();
}

SceneDirector::~SceneDirector() {
	//clear de los vectores y tal
}

void SceneDirector::changeScene(SceneEnum next_scene, bool load_on_return, bool history) {
	
	if (load_on_return) { _CurrentScene->unLoad(); }

	_CurrentScene->setLoaded(!load_on_return);
	_CurrentScene->leaveScene();

	if (history) { _SceneHistory.push(_CurrentScene); }

	//cambio de verdad
	_CurrentScene = _Scenes[next_scene];
}

void SceneDirector::goBack(bool load_on_return) {
	
	if (load_on_return) { _CurrentScene->unLoad(); }

	if (_SceneHistory.empty()) { return; }
	
	Scene* prevScene = _SceneHistory.top();
	
	if (prevScene != NULL) {
		//quito la tapa y la scena de debajo es el nuevo top
		_SceneHistory.pop();
		_CurrentScene->setLoaded(!load_on_return);
		_CurrentScene->leaveScene();
		_CurrentScene = prevScene;
	}

}
