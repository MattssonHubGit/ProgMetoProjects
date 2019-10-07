#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <vector>
#include "Player.h"
#include "Coin.h"

typedef std::vector<Entity*> EntityVector;

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	bool CheckGameOverState(Player* plyr, Coin* cn);
	void CollisionManagement();
	void AsteroidSpawner(float deltaTime);
	void EntityUpdate();
	void EntityRender();
	void EntityCleaner();
	void WindowsEventManager();
	sf::Texture* LoadTextureFromPath(std::string path);

	sf::Texture* playerTexture;
	sf::Texture* asteroidTexture;
	sf::Texture* coinTexture;

	sf::RenderWindow gameWindow;
	bool gameIsOver;
	float asteroidTimer;

	EntityVector entityList;
};