#pragma once
#include "Entity.h"

class Asteroid : public Entity 
{
public:	
	Asteroid(int posX, int posY, float dirX, float dirY);

private:
	float moveSpeed;
	float dirX;
	float dirY;

};