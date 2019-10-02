#pragma once
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "string.h"
#include "Coin.h"
#include "Player.h"
#include <iostream>


#pragma region NameSpaces
using namespace sf;
using namespace std;

//Settings
namespace {
	const string windowTitle = "Asteroids";
	const VideoMode videoMode = VideoMode((768/2), (1024/2));
	const Color backgroundColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;

	const int PLAYER_RADIUS = 30;
	const int COIN_RADIUS = 15;
}
#pragma endregion

Game::Game() :
	gameWindow(videoMode, windowTitle, Style::Titlebar | Style::Close),
	playerTexture(LoadTextureFromPath("ShipSprite.psd")),
	asteroidTexture(LoadTextureFromPath("AsteroidSprite.psd")),
	coinTexture(LoadTextureFromPath("CoinSprite.psd")),
	gameIsOver(false),
	entityList()
{

}

Game::~Game()
{
}
;


void Game::Run() 
{
	Player* player = new Player(videoMode.width/2, videoMode.height/2, videoMode.width, videoMode.height, PLAYER_RADIUS, "Player", 5, playerTexture);
	Coin* coin = new Coin(videoMode.width / 2, 0, videoMode.width, videoMode.height, COIN_RADIUS, "Coin", 2, coinTexture);

	entityList.push_back(player);
	entityList.push_back(coin);

	Clock frameClock;
	while (gameWindow.isOpen() && !gameIsOver)
	{
		//Management
		float deltaTime = frameClock.restart().asSeconds();
		gameWindow.setFramerateLimit(FRAMERATE_LIMIT);
		WindowsEventManager();

		//Debugging
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			gameIsOver = true;
		}

		//Things
		gameWindow.clear(backgroundColor);
		EntityUpdate();
		EntityRender();
		CollisionManagement();
		EntityCleaner();
		if (coin->markedDead)
		{
			cout << "coin dead" << endl;
		}
		gameWindow.display();
	}

}

Texture* Game::LoadTextureFromPath(string path)
{
	Texture* outputTexture = new Texture();
	if (!outputTexture->loadFromFile(path))
	{
		cout << "Error getting sprite" << endl;
	}
	return outputTexture;
}

void Game::EntityUpdate()
{
	for each (Entity* ent in entityList)
	{
		ent->Update();
	}
}

void Game::EntityRender()
{
	for each (Entity* ent in entityList)
	{
		ent->Render(gameWindow);
	}
}

void Game::EntityCleaner() 
{
	//Remove entities that have been marked for death
	for (EntityVector::size_type i = 0; i < entityList.size(); i++) 
	{
		if (entityList[i]->markedDead)
		{
			delete entityList[i];
			entityList.erase(entityList.begin() + i);
		}
	}
}

void Game::WindowsEventManager() 
{
	Event closeEvent;
	while (gameWindow.pollEvent(closeEvent))
	{
		if (closeEvent.type == Event::Closed)
		{
			gameWindow.close();
		}
	}
}

void Game::CollisionManagement() 
{
	//Checks every entity against every other entity. 
	//If their radius overlaps, call their OnCollision functions...
	//...with their respective CollisionId passed as arguements.
	for (EntityVector::size_type i = 0; i < entityList.size(); i++) {
		for (EntityVector::size_type j = i + 1; j < entityList.size(); j++) {
			int dx = (entityList[i]->posX - entityList[j]->posX);
			int dy = (entityList[i]->posY - entityList[j]->posY);
			float distance = powf((dx * dx + dy * dy), 0.5);

			if (distance < (entityList[i]->radius + entityList[j]->radius)) {
				entityList[i]->OnCollision(entityList[j]->CollisionId);
				entityList[j]->OnCollision(entityList[i]->CollisionId);
			}
		}
	}
}
