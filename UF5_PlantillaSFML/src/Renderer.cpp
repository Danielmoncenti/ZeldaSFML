#include "Renderer.h"
#include "singletons.h"

Renderer* Renderer::instance = NULL;

void Renderer::setFramerate(int framerate) {
	_Window->setFramerateLimit(framerate);
}

Renderer* Renderer::getInstance() {
	if (instance == NULL) {
		instance = new Renderer();
	}
	return instance;
}

Renderer::Renderer() {
	if (instance != NULL) { return; }
	_Window = NULL;
	initWindow();
}

Renderer::~Renderer() {

}

void Renderer::initWindow() {

	// tamaño estatico de pantalla 
	_windowWidth = SCREEN_WIDTH;
	_windowHeight = SCREEN_HEIGHT;

	//creacion de la ventana con tamaños y titulo 
	_Window = new sf::RenderWindow(sf::VideoMode(_windowWidth, _windowHeight), WINDOW_TITLE);
}

void Renderer::windowClear() {
	//Usamos una funcion de SFML
	_Window->clear(sf::Color::Black);
}

void Renderer::windowRefresh() {
	//Usamos una funcion de SFML
	_Window->display();
}

bool Renderer::windowIsOpen() {
	//Usamos una funcion de SFML
	return _Window->isOpen();
}

void Renderer::drawRectangle(C_Rectangle rect, Color col, bool outline) {
	//Usamos funciones de SFML
	sf::RectangleShape shape_rect;
	sf::Color color = sf::Color(col.r, col.g, col.b);
	if (!outline) {
		shape_rect.setFillColor(color);
	}
	else {
		shape_rect.setFillColor(sf::Color(0,0,0,0));
	}
	shape_rect.setOutlineThickness(1);
	shape_rect.setOutlineColor(color);
	shape_rect.setPosition(sf::Vector2f(rect.x, rect.y));
	shape_rect.setSize(sf::Vector2f(rect.w, rect.h));

	_Window->draw(shape_rect);
	
}

void Renderer::drawSprite(int ID, int posX, int posY, C_Rectangle rect) {
	if (ID == -1) { return; }
	sf::Sprite* spr = sResManager->getSpriteByID(ID);
	spr->setTextureRect(sf::IntRect(rect.x, rect.y, rect.w, rect.h));
	spr->setPosition(sf::Vector2f(posX, posY));
	
	_Window->draw(*spr);

}


