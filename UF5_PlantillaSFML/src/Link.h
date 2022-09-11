#ifndef LINK_H
#define LINK_H

#include "Utils.h"
#include "Entity.h"

enum AttackDirecctions { A_NONE, A_UP, A_DOWN, A_LEFT, A_RIGHT };

class Link : public Entity {
	public:
		Link();
		~Link();

		void init(int x, int y);
		void update();
		void render();
		isClass isofClass() { return LINK; };
		unsigned int GetHP();
		int EnemyHitted(Entity* ent);
		void GetHit();
		void  HpUp();
		void RestartPlayerPos();
	
	protected:
		Directions getNextDirection();
		AttackDirecctions GetDirectionAttack();
		unsigned int life;
		unsigned int Hp;
		bool Attacking;
		C_Rectangle	AttackHitbox;
		C_Rectangle attack_rect;
		int	Attack_Duration = 500;
		int	Attack_time = 0;
		int	AttackHitBoxSprite_Id;
		int	AttackHitBoxSprite_X;
		int	AttackHitBoxSprite_Y;
		AttackDirecctions AttackDir;
};

#endif