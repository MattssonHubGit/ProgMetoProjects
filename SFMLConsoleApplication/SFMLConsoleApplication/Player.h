#pragma once
#include "Entity.h"

class Player : public Entity 
{
public:
	Player(int posX, int posY);

private:
	float moveSpeed;
};