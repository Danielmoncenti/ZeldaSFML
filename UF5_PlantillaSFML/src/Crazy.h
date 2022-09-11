#pragma once

#include "Utils.h"
#include "Entity.h"
#include "time.h"

class Crazy : public Entity {

	public:
		Crazy();
		~Crazy();

		void init(int x, int y);
		void update();
		void render();

		bool isAlive() { return mpAlive; }

		void GetHit();

		isClass isofClass() { return CRAZY; };

		C_Rectangle getRect() { return _Rect; }

	protected:
		C_Rectangle _Rect; //Collision and position

		Directions getNextDirection();
};
