#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class Entity
{
public: 
	int posX;
	int posY;
	float radius;
	bool markedDead;
	std::string CollisionId;
	void OnCollision(std::string CollisionId);

protected:
	void MovementManagement();
};
