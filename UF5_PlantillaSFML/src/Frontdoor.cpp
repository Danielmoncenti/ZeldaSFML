#include "Frontdoor.h"
#include "singletons.h"

Frontdoor::Frontdoor() : Entity() {

}

Frontdoor ::~Frontdoor() {
}

void Frontdoor::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/ClosedDoor2.png");
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

void Frontdoor::update() {

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	if (isOpen) { sprite_id = sResManager->getSpriteID("assets/OpenDoor.png"); }
	else { sprite_id = sResManager->getSpriteID("assets/ClosedDoor2.png"); }
}

void Frontdoor::render() {
	Entity::render();
}

bool Frontdoor::IsOpen()
{
	return isOpen;
}

void Frontdoor::OpenDoor() {
	isOpen = true;
}

void Frontdoor::SetMap(int map)
{
	goesToMap = map;
}
