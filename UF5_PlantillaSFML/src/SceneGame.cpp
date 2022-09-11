#include "SceneGame.h"
#include "singletons.h"

SceneGame::SceneGame() : Scene() {

}

SceneGame::~SceneGame() {

}

void SceneGame::preLoad() {


}

void SceneGame::unLoad() {

}

void SceneGame::init() {

	actualMap = 0;
	playerX = 0;
	playerY = 0;
	ghostX = 0;
	ghostY = 0;
	boundX = 0;
	boundY = 0;
	crazyX = 0;
	CrazyY = 0;
	frontdoorX = 0;
	frontdoorY = 0;
	backdoorX = 0;
	backdoorY = 0;
	
	_Link = new Link();
	
	initMap("1",0);
	initMap("2", 1);
	initMap("3", 2);
	initMap("4", 3);

	hearts_id = sResManager->getSpriteID("assets/hearts.png");	
	Wall_id = sResManager->getSpriteID("assets/wall.png");
	Wall_rect = C_Rectangle{ 0, 0, TILE_SIZE   , TILE_SIZE };
}

void SceneGame::enterScene() {
	sSoundManager->playMusic("assets/Audios/gamesong.flac");
}

void SceneGame::updateBegin() {

	sprite_frame_time += global_delta_time;
	if (sprite_frame_time > 100) {
		sprite_frame_time = 0;
		sprite_frame++;
		if (sprite_frame >= 8) {
			sprite_frame = 0;
		}
		sprite_rect.x = sprite_rect.w * sprite_frame;
	}
}

void SceneGame::update() {

	hearts_rect = C_Rectangle{ 0, 0, TILE_SIZE * _Link->GetHP(), TILE_SIZE };

	/*if (sInput->isKeyPressed(Input::KEY_T)) {
		actualMap++;
		
		changeMap(actualMap);

	}
	if (sInput->isKeyPressed(Input::KEY_Y)) {
		actualMap--;
		
		changeMap(actualMap);
	}*/
	
	_Link->update();

	playerX = _Link->GetPosX();
	playerY = _Link->GetPosY();


	int sizeE = _maps[actualMap].mEntities.size();
	for (size_t i = 0; i < sizeE; i++) {
		if (_maps[actualMap].mEntities[i]->isAlive()) {

			int HittedEnemy = _Link->EnemyHitted(_maps[actualMap].mEntities[i]);
			switch (HittedEnemy) 
			{
				case GHOST:
					_maps[actualMap].mEntities[i]->GetHit();
					_maps[actualMap].left--;
					break;
				case CRAZY:
					_maps[actualMap].mEntities[i]->GetHit();
					_maps[actualMap].left--;
					break;
				case BOUND:
					_maps[actualMap].mEntities[i]->GetHit();
					_maps[actualMap].left--;
					break;
				default:
					break;
			}

			switch (_maps[actualMap].mEntities[i]->isofClass()) 
			{
				default:
					break;
				case GHOST:
					_maps[actualMap].mEntities[i]->SetLinkPosition(playerX, playerY);
					break;
				case BACKDOOR:
					if (_maps[actualMap].left == 0) {
						_maps[actualMap].mEntities[i]->OpenDoor();
					}
					break;
				case FRONTDOOR:
					if (_maps[actualMap].left == 0) {
						_maps[actualMap].mEntities[i]->OpenDoor();
					}
					break;
			}

			int collision = _Link->collidesWith(_maps[actualMap].mEntities[i]);
			switch (collision) 
			{
				default:
					break;
				case GHOST:
					_Link->GetHit();
					break;
				case CRAZY:
					_Link->GetHit();
					break;
				case BOUND:
					_Link->GetHit();
					break;
			
				case BACKDOOR:
					if (_maps[actualMap].left<=0) {
						backmap = true;
					}
					break;
				case FRONTDOOR:
					if (_maps[actualMap].left <= 0) {
						frontmap = true;
					}
					break;
				case HEART:
					_Link->HpUp();
					_maps[actualMap].mEntities[i]->GetHit();
					break;
			}
		}
		_maps[actualMap].mEntities[i]->update();
	}

	if (frontmap) {
		frontmap = false;
		actualMap++;
		changeMap(actualMap);
		_Link->RestartPlayerPos();

	}
	else if (backmap) {
		backmap = false;
		actualMap--;
		changeMap(actualMap);
		_Link->RestartPlayerPos();
	}
}

void SceneGame::updateEnd() {

}

void SceneGame::renderBegin() {

	for (int i = 0; i < _mapH; i++) {
		for (int j = 0; j < _mapW; j++) {
			if (_maps[actualMap].mpCollisionMap[i][j]) {

				sRenderer->drawSprite(Wall_id, j * TILE_SIZE, i * TILE_SIZE, Wall_rect);
			}
		}
	}

}

void SceneGame::render() {

	int size = _maps[actualMap].mEntities.size();
	for (size_t i = 0; i < size; i++) {
		if (_maps[actualMap].mEntities[i]->isAlive()) {
			_maps[actualMap].mEntities[i]->render();
		}
	}
}

void SceneGame::renderEnd() {

	if (_Link->isAlive()) {
		_Link->render();
	}
	sRenderer->drawSprite(hearts_id, 13*TILE_SIZE, 15*TILE_SIZE, hearts_rect);
}

void SceneGame::renderGUI() {
	
}

void SceneGame::changeMap(int &_actualmap)
{
	_Link->setCollisionsMap(&_maps[_actualmap].mpCollisionMap, 30, 15);
}

void SceneGame::initMap(std::string map, int _whatmap) {

	std::fstream file;
	file.open("assets/Map" + map + ".txt", std::ios::in);
	if (!file.is_open()) {
		std::cout << "Error: map is not found" << std::endl;
		system("pause");
		exit(0);
	}

	//Leer ancho y alto del mapa desde el txt
	std::string line;
	std::getline(file, line);
	int width = atoi(line.c_str());
	std::getline(file, line);
	int height = atoi(line.c_str());


	//Redimensionar el vector
	_maps[_whatmap].mpCollisionMap.resize(height);
	for (size_t i = 0; i < height; i++) {
		_maps[_whatmap].mpCollisionMap[i].resize(width, false);
		std::getline(file, line);
		for (size_t j = 0; j < width; j++) {
			char a_char = line[j];
			switch (a_char) {
				default:
					break;
				case '#':
					_maps[_whatmap].mpCollisionMap[i][j] = true;
					break;
				case '1':
				{ //crear fantasmas
					Frontdoor* aFrontdoor = new Frontdoor();
					frontdoorX = j * TILE_SIZE;
					frontdoorY = i * TILE_SIZE;
					aFrontdoor->init(frontdoorX, frontdoorY);
					aFrontdoor->setCollisionsMap(&_maps[_whatmap].mpCollisionMap, width, height);
					_maps[_whatmap].mEntities.push_back(aFrontdoor);
				}break;
				case '2':
				{ //crear fantasmas
					Backdoor* aBackdoor = new Backdoor();
					backdoorX = j * TILE_SIZE;
					backdoorY = i * TILE_SIZE;
					aBackdoor->init(backdoorX, backdoorY);
					aBackdoor->setCollisionsMap(&_maps[_whatmap].mpCollisionMap, width, height);
					_maps[_whatmap].mEntities.push_back(aBackdoor);
				}break;
				case 'L': 
				{
					playerX = j * TILE_SIZE;
					playerY = i * TILE_SIZE;
					_Link->init(playerX, playerY);
					_Link->setCollisionsMap(&_maps[0].mpCollisionMap, width, height);
				}break;
				case 'H':
				{ //crear fantasmas
					Heart* aHeart = new Heart();
					heartX = j * TILE_SIZE;
					heartY = i * TILE_SIZE;
					aHeart->init(heartX, heartY);
					aHeart->setCollisionsMap(&_maps[_whatmap].mpCollisionMap, width, height);
					_maps[_whatmap].mEntities.push_back(aHeart);
				}break;
				case 'F': 
				{
					Ghost* aGhost = new Ghost();
					ghostX = j * TILE_SIZE;
					ghostY = i * TILE_SIZE;
					aGhost->init(ghostX, ghostY);
					aGhost->setCollisionsMap(&_maps[_whatmap].mpCollisionMap, width, height);
					_maps[_whatmap].mEntities.push_back(aGhost);
					_maps[_whatmap].left++;
				}break;
				case 'C': 
				{
					Crazy* aCrazy = new Crazy();
					crazyX = j * TILE_SIZE;
					CrazyY = i * TILE_SIZE;
					aCrazy->init(crazyX, CrazyY);
					aCrazy->setCollisionsMap(&_maps[_whatmap].mpCollisionMap, width, height);
					_maps[_whatmap].mEntities.push_back(aCrazy);
					_maps[_whatmap].left++;
				}break;
				case 'B': 
				{
					Bound* aBound = new Bound();
					boundX = j * TILE_SIZE;
					boundY = i * TILE_SIZE;
					aBound->init(boundX, boundY);
					aBound->setCollisionsMap(&_maps[_whatmap].mpCollisionMap, width, height);
					_maps[_whatmap].mEntities.push_back(aBound);
					_maps[_whatmap].left++;
				}break;

			}
		}
	}

	_mapW = width;
	_mapH = height;


	file.close();
}

