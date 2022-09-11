#ifndef DOOR_H
#define DOOR_H

#include "Utils.h"
#include "Entity.h"

class Door : public Entity{

	public:
		Door();
		~Door();
		void init(int x, int y);
		void update();
		void render();
		isClass getClassName() { return DOOR; };
		bool IsOpen();
		void OpenDoor();

	protected:
		bool isOpen;
};


#endif

