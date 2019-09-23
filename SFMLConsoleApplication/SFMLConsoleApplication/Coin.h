#pragma once

#include "Entity.h"

class Coin : public Entity 
{
public: 
	Coin(int posX, int posY);
	bool taken;

private:
	float moveSpeed;
	int dirY;

};
