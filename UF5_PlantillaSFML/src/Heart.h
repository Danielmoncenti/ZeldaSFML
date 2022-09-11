#pragma once

#include "Utils.h"
#include "Entity.h"

class Heart : public Entity {

public:
	Heart();
	~Heart();

	void init(int x, int y);
	void update();
	void render();

	isClass isofClass() { return HEART; };


	void SetMap(int map);

protected:
	bool isOpen;
	int goesToMap;
};




#pragma once
