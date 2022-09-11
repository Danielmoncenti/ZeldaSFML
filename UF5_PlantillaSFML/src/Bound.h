#pragma once

#include "Utils.h"
#include "Entity.h"
#include "time.h"

class Bound : public Entity {

	public:
		Bound();
		~Bound();

		void init(int x, int y);
		void update();
		void render();

		bool isAlive() { return mpAlive; }

		void GetHit();

		isClass isofClass() { return BOUND; };

		C_Rectangle getRect() { return _Rect; }

	protected:
		C_Rectangle _Rect; //Collision and position
		int nextdir=1;
		Directions getNextDirection();
	
};
