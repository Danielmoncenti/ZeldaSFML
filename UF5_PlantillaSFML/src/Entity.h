#ifndef ENTITY_H
#define ENTITY_H

#include "Utils.h"

enum Directions { NONE, UP, DOWN, LEFT, RIGHT };
enum isClass { ENTITY, LINK, DOOR, GHOST, CRAZY, BOUND, BACKDOOR, FRONTDOOR , HEART};

class  Entity {
	public:
		Entity();
		~Entity();

		virtual void init(int x, int y);
		virtual void update();
		virtual void render();
		virtual isClass isofClass() { return ENTITY; }

		bool isAlive() { return mpAlive; }
		void setAlive(bool alive);

		void setCollisionsMap(std::vector<std::vector<bool>>* colmap, int w, int h);
		C_Rectangle getRect() { return mpRect; };
		int collidesWith(Entity* ent);
		
		int GetPosX();
		int GetPosY();
		virtual void GetHit();
		virtual void SetLinkPosition(int X, int Y);
		virtual void OpenDoor();
		virtual bool IsOpen();

	protected:
		C_Rectangle mpRect;
		
		virtual Directions getNextDirection();
		void updateControls();
		void move();
		bool checkCollisionsWithMap();

		std::vector<std::vector<bool>>* mpColMap;
		int mMapWidth;
		int mMapHeight;

		bool mpMoving;
		int mpSpeed;
		int currentSpeed;
		int mpDirection;

		int mpXtoGo;
		int mpYtoGo;

		bool mpAlive;

		int				sprite_id;
		C_Rectangle		sprite_rect;
		int				sprite_frame;
		int				sprite_frame_time;
		int				sprite_x;
		int				sprite_y;

};

#endif