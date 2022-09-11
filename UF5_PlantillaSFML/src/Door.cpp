#include "Door.h"
#include "singletons.h"

Door::Door() : Entity() {

}

Door ::~Door() {
}

void Door::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("Assets/door.png");
	sprite_rect = C_Rectangle{ 0, 0, 32, 32 };
	
	mpRect.x = x;
	mpRect.y = y;
	mpRect.h = 16;
	mpRect.w = 16;
	mpXtoGo = x;
	mpYtoGo = y;
	isOpen = false;
}

void Door::update() {

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	if (isOpen) { sprite_id = sResManager->getSpriteID("Assets/link2.png"); }
	else { sprite_id = sResManager->getSpriteID("Assets/link2.png"); }
}

void Door::render() {
	Entity::render();
}

bool Door::IsOpen() {
	return isOpen;
}

void Door::OpenDoor(){
	isOpen = true;
}
