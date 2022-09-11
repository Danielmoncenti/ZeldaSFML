#pragma once

#include "includes.h"
#include <SFML/Graphics.hpp>

class Renderer {

	public:
		Renderer();
		~Renderer();

		//! Inits the screen
		void initWindow();

		//! Clean Window to dont duplicate the images
		void windowClear();

		//! Performs Screen Draw (screen flip) "frame rate"
		void windowRefresh();

		//! Returns true if window exists
		bool windowIsOpen();

		//! Rectangle Shape draw
		// Tercer argunmento sera false por defecto, puedes ahorrarte poner el parametro
		void drawRectangle(C_Rectangle rect, Color col, bool outline = false); 

		//! Sprite draw
		void drawSprite(int ID, int posX, int posY, C_Rectangle rect);

		//! Returns the window pointer from library
		//! To get information that we will later
		sf::RenderWindow* getWindow() { return _Window; };

		//! Limit framerate
		void setFramerate(int framerate);


		//! This Class is Singleton
		static Renderer* getInstance();


	private:
		static Renderer* instance;

		sf::RenderWindow* _Window;

		int _windowWidth;
		int _windowHeight;
};
