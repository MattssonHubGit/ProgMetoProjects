#pragma once
#include "Entity.h"

class Asteroid : public Entity 
{
public:	
	Asteroid(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture);
	~Asteroid();

	void OnCollision(std::string CollisionId) override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;

private:
	float moveSpeed;
	int dirY;
	int boundryX;
	int boundryY;
	void MovementManagement() override;
	void ReadyGFX(sf::Texture* texture) override;
	void UnloadGFX() override;

};