#pragma once
#include "Entity.h"

class Player : public Entity 
{
public:
	Player(int iniX, int iniY, float iniRad, std::string colId, float speed, sf::Texture* texture);
	~Player();
	void OnCollision(std::string CollisionId) override;
	void Update() override;
	void Render(sf::RenderWindow &window) override;

private:
	float moveSpeed;
	void MovementManagement() override;
	void ReadyGFX(sf::Texture *texture) override;
	void UnloadGFX() override;
};