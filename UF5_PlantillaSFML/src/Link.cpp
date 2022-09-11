#include "Link.h"
#include "singletons.h"

Link::Link() : Entity() {

}

Link::~Link(){
}

void Link::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("assets/link3.png");
	AttackHitBoxSprite_Id = sResManager->getSpriteID("assets/attack.png");
	sprite_rect = C_Rectangle{ 0, 0, TILE_SIZE, TILE_SIZE };
	attack_rect = C_Rectangle{ 0, 0, TILE_SIZE, TILE_SIZE };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	Hp = 3;
	life = 3;
	mpSpeed = 125;
}

void Link::update(){
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
		if (Attacking)
		{
			switch (mpDirection)
			{
			default:
				break;
			case UP:
				sprite_rect = C_Rectangle{ 2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case DOWN:
				sprite_rect = C_Rectangle{ 1 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case RIGHT:
				sprite_rect = C_Rectangle{ 0, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case LEFT:
				sprite_rect = C_Rectangle{ 1 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			}
		}
		else {
			switch (mpDirection)
			{
			default:
				break;
			case UP:
				sprite_rect = C_Rectangle{ 2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };
				break;
			case DOWN:
				sprite_rect = C_Rectangle{ 0, 0, TILE_SIZE, TILE_SIZE };
				break;
			case RIGHT:
				sprite_rect = C_Rectangle{ 0, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				break;
			case LEFT:
				sprite_rect = C_Rectangle{ 1 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };
				break;
			}

		}
	}
	else {
		mpMoving = false;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	if (GetDirectionAttack() != A_NONE && !Attacking) {
		Attacking = true;
		AttackDir = GetDirectionAttack();
		//sonido de ataque
		sSoundManager->playSound("assets/Audios/attack.wav");
	}

	switch (AttackDir)
	{
		case A_UP:
			AttackHitBoxSprite_Y = sprite_y - TILE_SIZE;
			AttackHitBoxSprite_X = sprite_x;
			AttackHitbox = C_Rectangle{ AttackHitBoxSprite_X, AttackHitBoxSprite_Y, TILE_SIZE, TILE_SIZE };
			break;
		case A_DOWN:
			AttackHitBoxSprite_Y = sprite_y + TILE_SIZE;
			AttackHitBoxSprite_X = sprite_x;
			AttackHitbox = C_Rectangle{ AttackHitBoxSprite_X, AttackHitBoxSprite_Y, TILE_SIZE, TILE_SIZE };
			break;
		case A_LEFT:
			AttackHitBoxSprite_Y = sprite_y;
			AttackHitBoxSprite_X = sprite_x - TILE_SIZE;
			AttackHitbox = C_Rectangle{ AttackHitBoxSprite_X, AttackHitBoxSprite_Y, TILE_SIZE, TILE_SIZE };
			break;
		case A_RIGHT:
			AttackHitBoxSprite_Y = sprite_y;
			AttackHitBoxSprite_X = sprite_x + TILE_SIZE;
			AttackHitbox = C_Rectangle{ AttackHitBoxSprite_X, AttackHitBoxSprite_Y, TILE_SIZE, TILE_SIZE };
			break;
		default:
			break;
	}
	
	if (Attacking)
	{
		Attack_time += global_delta_time;

		if (Attack_time > Attack_Duration)
		{
			Attack_time = 0;
			Attacking = false;
		}
	}
}

void Link::render(){
	
	Entity::render();
	if (Attacking)
	{
		sRenderer->drawSprite(AttackHitBoxSprite_Id, AttackHitBoxSprite_X, AttackHitBoxSprite_Y, attack_rect);
	}
}

void Link::HpUp()
{
	if (Hp < 3) {
		Hp++;
	}
}

unsigned int Link::GetHP()
{
	return Hp;
}

int Link::EnemyHitted(Entity* ent)
{
	C_Rectangle rectEntity = ent->getRect();
	C_Rectangle rectHitbox = C_Rectangle{ AttackHitbox.x, AttackHitbox.y, AttackHitbox.w, AttackHitbox.h };
	if (C_RectangleCollision(rectHitbox, rectEntity) && Attacking)
	{
		return ent->isofClass();
	}
	else
	{
		return ENTITY;
	}
}

void Link::GetHit(){

	Hp--;
	mpRect.x = (mMapWidth - 2) * TILE_SIZE;
	mpXtoGo = mpRect.x;
	sSoundManager->playSound("assets/Audios/hurt.wav");
	
	if (Hp <= 0) {
		setAlive(false);
	}
}

void Link::RestartPlayerPos(){

	int checkX = mpRect.x / TILE_SIZE;

	if (checkX == 0) {
		mpRect.x = (mMapWidth - 2) * TILE_SIZE;
		mpXtoGo = mpRect.x;
	}
	else if (mMapWidth - 2 ) {
		mpRect.x = TILE_SIZE;
		mpXtoGo = mpRect.x;
	}

}

Directions Link::getNextDirection()
{
	Directions dir = NONE;

	if (sInput->isKeyDown(Input::KEY_A)) {
		dir = LEFT;
	}
	else if (sInput->isKeyDown(Input::KEY_D)) {
		dir = RIGHT;
	}
	else if (sInput->isKeyDown(Input::KEY_W)) {
		dir = UP;
	}
	else if (sInput->isKeyDown(Input::KEY_S)) {
		dir = DOWN;
	}

	return dir;
}

AttackDirecctions Link::GetDirectionAttack()
{
	AttackDirecctions CurrentADir;

	if (sInput->isKeyPressed(Input::ARROW_LEFT)) {
		CurrentADir = A_LEFT;

	}
	else if (sInput->isKeyPressed(Input::ARROW_RIGHT)) {
		CurrentADir = A_RIGHT;

	}
	else if (sInput->isKeyPressed(Input::ARROW_UP)) {
		CurrentADir = A_UP;
	}
	else if (sInput->isKeyPressed(Input::ARROW_DOWN)) {
		CurrentADir = A_DOWN;
	}
	else
	{
		CurrentADir = A_NONE;
	}

	return CurrentADir;
}
