#include "SceneMenu.h"
#include "singletons.h"

SceneMenu::SceneMenu() : Scene() {
	
}

SceneMenu::~SceneMenu() {

}

void SceneMenu::preLoad() {

}

void SceneMenu::unLoad() {

}

void SceneMenu::init() {
	menu_sprite_id = sResManager->getSpriteID("assets/menu.jpg");
	menu_sprite_rect = C_Rectangle{ 0, 0,
		sResManager->getSpriteWidth(menu_sprite_id),
		sResManager->getSpriteHeight(menu_sprite_id) 
	};
	_MenuOption = CONTINUE;
	_OptionSelector = C_Rectangle{ 745, 245, 150, 40 };
}

void SceneMenu::enterScene() {
	sSoundManager->playMusic("assets/Audios/zelda.ogg");
}


void SceneMenu::updateBegin() {
}

void SceneMenu::update() {
	int prevOption = _MenuOption;
	if (sInput->isKeyPressed(Input::ARROW_DOWN)) {
		_MenuOption++;
		if (_MenuOption > EXIT) {
			_MenuOption = EXIT;
		}
	}
	else if (sInput->isKeyPressed(Input::ARROW_UP)) {
		_MenuOption--;
		if (_MenuOption < CONTINUE) {
			_MenuOption = CONTINUE;
		}
	}

	if (prevOption != _MenuOption) {
		_OptionSelector.y = 250 + _MenuOption * 50;
	}

	if (sInput->isKeyPressed(Input::ENTER)) {
		sSoundManager->playSound("assets/Audios/coin.wav");
		switch (_MenuOption) {
			case NEW_GAME:
				sSoundManager->musicStop();
				sDirector->changeScene(SceneDirector::GAME, false);
				break;
			case EXIT:
				sInput->closeWindow();
				break;
		}
	}
}

void SceneMenu::updateEnd() {

}

void SceneMenu::renderBegin() {

}

void SceneMenu::render() {
	sRenderer->drawSprite(menu_sprite_id, 0, 0, menu_sprite_rect);
	sRenderer->drawRectangle(_OptionSelector, Color{ 255, 255, 255 }, true);
}

void SceneMenu::renderEnd() {

}

void SceneMenu::renderGUI() {

}
