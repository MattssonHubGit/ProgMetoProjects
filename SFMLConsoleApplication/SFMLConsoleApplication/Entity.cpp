#include "Entity.h"

Entity::Entity(int iniX, int iniY, float iniRadius, std::string colId) :
	posX(iniX),
	posY(iniY),
	radius(iniRadius),
	CollisionId(colId),
	markedDead(false)
{

};

Entity::~Entity() 
{

};