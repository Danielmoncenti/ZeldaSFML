#include "Heart.h"
#include "singletons.h"

Heart::Heart() : Entity() {

}

Heart ::~Heart() {
}

void Heart::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/hearts.png");
	sprite_rect = C_Rectangle{ 0, 0, 32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpRect.h = 32;
	mpRect.w = 32;
	mpXtoGo = x;
	mpYtoGo = y;
	isOpen = false;
	goesToMap = 0;
}

void Heart::update() {

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;



}

void Heart::render() {
	Entity::render();
}


void Heart::SetMap(int map)
{
	goesToMap = map;
}
