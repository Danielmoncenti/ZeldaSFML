#include "Bound.h"
#include "singletons.h"

Bound::Bound() : Entity() {

}

Bound::~Bound() {
}

void Bound::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/enemies1.png");
	sprite_rect = C_Rectangle{ 0, 0, 32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	mpSpeed = 60;
	srand(time(NULL));

}

void Bound::update() {
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
		switch (mpDirection)
		{
			default:
				break;
			case UP:
				sprite_rect = C_Rectangle{ 2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case DOWN:
				sprite_rect = C_Rectangle{ 0, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case RIGHT:
				sprite_rect = C_Rectangle{ 3 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case LEFT:
				sprite_rect = C_Rectangle{ 0, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
		}
	}
	else {
		mpMoving = false;
		nextdir *=-1;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;


}

void Bound::render() {
	Entity::render();
}



void Bound::GetHit() {
	setAlive(false);
}

Directions Bound::getNextDirection() {
	Directions _direction;
	if (nextdir == 1) {
		_direction = UP;
	}
	else if (nextdir == -1) {
		_direction = DOWN;
	}
	if (_direction != NONE) {
		mpMoving = true;
	}
	return  _direction;
}

