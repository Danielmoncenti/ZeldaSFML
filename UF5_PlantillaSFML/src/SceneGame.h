#pragma once
#include"ResourceManager.h"
#include "Scene.h"
#include "Utils.h"
#include "Entity.h"
#include "Link.h"
#include "Door.h"
#include "input.h"
#include "Ghost.h"
#include "Crazy.h"
#include "Bound.h"
#include "Frontdoor.h"
#include"Backdoor.h"
#include "Heart.h"


class SceneGame : public Scene {
	public:
		SceneGame();
		~SceneGame();

		virtual void preLoad();
		virtual void unLoad(); //Liberar memoria sin borrar el puntero

	protected:
		virtual void init();
		virtual void enterScene();

		virtual void updateBegin();
		virtual void update();
		virtual void updateEnd();

		virtual void renderBegin();
		virtual void render();
		virtual void renderEnd();

		virtual void renderGUI();
		virtual void changeMap(int& _actualmap);

		void initMap(std::string, int _whatmap);
		void StartGame();
		void SaveCurrentMap();
		void LoadNextMap();
		void SaveLastMapStaus();

	private:
		C_Rectangle rect1;
		C_Rectangle rect2;

		int sprite_id;
		C_Rectangle sprite_rect;

		C_Rectangle hearts_rect;
		int hearts_id;

		//de prueba 
		int sprite_frame;
		int sprite_frame_time;
		struct maps
		{
			std::vector<std::vector<bool>> mpCollisionMap;
			std::vector<Entity*> mEntities;
			int left = 0;
		};
		maps _maps[4];
		int _mapW, _mapH;
		int playerX, playerY, ghostX, ghostY, crazyX, CrazyY, boundX, boundY, frontdoorX, frontdoorY, backdoorX, backdoorY, heartX, heartY;
		bool win, lose, record;
		int actualMap;
		bool frontmap;
		bool backmap;

		int	Wall_id;
		int	Wall_x;
		int	Wall_y;
		C_Rectangle Wall_rect;

		std::string CurrentMap;
		int TotalEnemies;
		int EnemiesDead;

		Input _sceneIput;
		Link* _Link;
};
