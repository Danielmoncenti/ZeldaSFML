#include "Crazy.h"
#include "singletons.h"

Crazy::Crazy() : Entity() {

}

Crazy::~Crazy() {
}

void Crazy::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/enemies1.png");
	sprite_rect = C_Rectangle{ 0, 0, 32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	mpSpeed = 60;
	srand(time(NULL));

}

void Crazy::update() {
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
		switch (mpDirection)
		{
			default:
				break;
			case UP:
				sprite_rect = C_Rectangle{ 2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };
				break;
			case DOWN:
				sprite_rect = C_Rectangle{ 0, 0, TILE_SIZE, TILE_SIZE };
				break;
			case RIGHT:
				sprite_rect = C_Rectangle{ 3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };
				break;
			case LEFT:
				sprite_rect = C_Rectangle{ 1 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };
				break;
		}
	}
	else {
		mpMoving = false;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

}

void Crazy::render() {
	Entity::render();
}



void Crazy::GetHit() {
	setAlive(false);
}

Directions Crazy::getNextDirection() {

	Directions _direction = (Directions)(rand() % 4 + 1);
	if (_direction != NONE) {
		mpMoving = true;
	}
	return _direction;
}
