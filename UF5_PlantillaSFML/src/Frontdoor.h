#ifndef FRONTDOOR_H
#define FRONTDOOR_H

#include "Utils.h"
#include "Entity.h"

class Frontdoor : public Entity {

	public:
		Frontdoor();
		~Frontdoor();

		void init(int x, int y);
		void update();
		void render();

		isClass isofClass() { return FRONTDOOR; };

		bool IsOpen();
		void OpenDoor();

		int GoesTo() { return goesToMap; };
		void SetMap(int map);

	protected:
		bool isOpen;
		int goesToMap;
};

#endif
