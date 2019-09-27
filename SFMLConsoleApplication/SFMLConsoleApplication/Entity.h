#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class Entity
{
public: 
	Entity(int iniX, int iniY, float iniRadius, std::string colId);
	~Entity();
	int posX;
	int posY;
	float radius;
	bool markedDead;
	std::string CollisionId;
	virtual void OnCollision(std::string CollisionId) = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow &renderWindow) = 0;

protected:
	virtual void MovementManagement() = 0;
	virtual void ReadyGFX(sf::Texture *texture) = 0;
	virtual void UnloadGFX() = 0;
	sf::Sprite* mySprite;
};
