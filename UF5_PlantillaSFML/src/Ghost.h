#pragma once

#include "Utils.h"
#include "Entity.h"


class Ghost : public Entity {

	public:
		Ghost();
		~Ghost();

		void init(int x, int y);
		void update();
		void render();

		bool isAlive() { return mpAlive; }

		void SetLinkPosition(int x, int y);
		void GetHit();

		isClass isofClass() { return GHOST; }

		C_Rectangle getRect() { return _Rect; };

	protected:
		C_Rectangle _Rect; //Collision and position

		Directions getNextDirection();

		int LinkX;
		int LinkY;

};
