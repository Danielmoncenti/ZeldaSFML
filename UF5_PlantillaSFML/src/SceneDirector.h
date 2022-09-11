#pragma once

#include "includes.h"
#include "Scene.h"


class SceneDirector
{
	public:
		enum SceneEnum{
			MAIN_MENU, GAME, /*GAME_OVER, WIN ...*/
			LAST_NO_USE
		};
		const SceneEnum FIRST_SCENE = SceneDirector::MAIN_MENU;

		SceneDirector();
		~SceneDirector();

		void changeScene(SceneEnum next_scene, bool load_on_return = true, bool history = true);
		void goBack(bool load_on_return = true);
		Scene* getCurrentScene() { return _CurrentScene; };

		static SceneDirector* getInstance();

	private:
		void initScenes();
		static SceneDirector* instance;

		Scene* _CurrentScene;
		std::vector<Scene*> _Scenes; //Todas las scenas del juego
		std::stack<Scene*> _SceneHistory; //Historial para poder ir hacia atras

};