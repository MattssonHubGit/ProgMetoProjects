#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	void CollisionManagement();
	void AsteroidManager();
	void CoinManager();
	void EntityMovement();
	void EntityRemoval();
	void WindowsEventManager();
	sf::Texture* LoadTextureFromPath(std::string path);

	sf::Texture* playerTexture;
	sf::Texture* asteroidTexture;
	sf::Texture* coinTexture;

	sf::RenderWindow gameWindow;
	bool gameIsOver;
};