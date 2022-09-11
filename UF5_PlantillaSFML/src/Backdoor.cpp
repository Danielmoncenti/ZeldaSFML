#include "Backdoor.h"
#include "singletons.h"

Backdoor::Backdoor() : Entity() {

}

Backdoor ::~Backdoor() {
}

void Backdoor::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/ClosedDoor.png");
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

void Backdoor::update() {

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	if (isOpen) { sprite_id = sResManager->getSpriteID("assets/OpenDoor.png"); }
	else { sprite_id = sResManager->getSpriteID("assets/ClosedDoor.png"); }
}

void Backdoor::render() {
	Entity::render();
}

bool Backdoor::IsOpen()
{
	return isOpen;
}

void Backdoor::OpenDoor() {
	isOpen = true;
}

void Backdoor::SetMap(int map)
{
	goesToMap = map;
}
