#pragma once

#include "Scene.h"

class SceneMenu : public Scene {
	public:
		enum MenuOptions{ CONTINUE, NEW_GAME, EXIT };
		SceneMenu();
		~SceneMenu();

		virtual void preLoad();
		virtual void unLoad(); //Liberar memoria sin borrar el puntero

	protected:
		virtual void init();
		virtual void enterScene();

		virtual void updateBegin();
		virtual void update();
		virtual void updateEnd();

		virtual void renderBegin();
		virtual void render();
		virtual void renderEnd();

		virtual void renderGUI();

	private:
		int menu_sprite_id;
		C_Rectangle menu_sprite_rect;

		int _MenuOption;
		C_Rectangle _OptionSelector;
};
