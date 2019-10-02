#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <vector>

typedef std::vector<Entity*> EntityVector;

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	bool CheckGameOverState();
	void CollisionManagement();
	void AsteroidSpawner();
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

	EntityVector entityList;
};