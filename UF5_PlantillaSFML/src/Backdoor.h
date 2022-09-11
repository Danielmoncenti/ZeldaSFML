#ifndef BACKDOOR_H
#define BACKDOOR_H

#include "Utils.h"
#include "Entity.h"

class Backdoor : public Entity {

	public:
		Backdoor();
		~Backdoor();

		void init(int x, int y);
		void update();
		void render();

		isClass isofClass() { return BACKDOOR; };

		bool IsOpen();
		void OpenDoor();

		int GoesTo() { return goesToMap; };
		void SetMap(int map);

	protected:
		bool isOpen;
		int goesToMap;
};


#endif
