#pragma once
#include <string>

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
