#include "Ghost.h"
#include "singletons.h"

Ghost::Ghost() : Entity() {

}

Ghost::~Ghost() {
}

void Ghost::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/enemies1.png");
	sprite_rect = C_Rectangle{ 0, 0, 32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	mpSpeed = 60;
}

void Ghost::update() {
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
		switch (mpDirection)
		{
			default:
				break;
			case UP:
				sprite_rect = C_Rectangle{ 2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case DOWN:
				sprite_rect = C_Rectangle{ 0, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case RIGHT:
				sprite_rect = C_Rectangle{ 3 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case LEFT:
				sprite_rect = C_Rectangle{ 0, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
		}
	}
	else {
		mpMoving = false;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

}

void Ghost::render() {
	Entity::render();
}

void Ghost::SetLinkPosition(int x, int y) {
	LinkX = x;
	LinkY = y;
}

void Ghost::GetHit() {
	setAlive(false);
}

Directions Ghost::getNextDirection() {

	Directions direction = NONE;

	if (LinkX < mpRect.x){
		direction = LEFT;
	}
	else if (LinkX > mpRect.x){
		direction = RIGHT;
	}
	else if (LinkY < mpRect.y){
		direction = UP;
	}
	else if (LinkY > mpRect.y){
		direction = DOWN;
	}

	return direction;
}
