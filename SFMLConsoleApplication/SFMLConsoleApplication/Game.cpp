#pragma once
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "string.h"
#include "Coin.h"
#include "Player.h"
#include "Asteroid.h"
#include <iostream>


#pragma region NameSpaces
using namespace sf;
using namespace std;

//Settings
namespace {
	//Video
	const string WINDOW_TITLE = "Asteroids";
	const VideoMode VIDEO_MODE = VideoMode((768/2), (1024/2));
	const Color BACKGROUND_COLOR = Color::Black;
	const int FRAMERATE_LIMIT = 60;

	//Radius
	const int PLAYER_RADIUS = 30;
	const int COIN_RADIUS = 15;
	const int ASTEROID_RADIUS = 30;

	//Player
	const float PLAYER_SPEED_BASE = 5;

	//Coin
	const float COIN_SPEED_BASE = 3;

	//Asteroids
	float asteroid_spawn_rate = 1;
	const float ASTEROID_ACCELERATION_RATE = 0.1f;
	const float ASTEROID_SPAWN_RATE_MAX = 5;
}
#pragma endregion

Game::Game() :
	gameWindow(VIDEO_MODE, WINDOW_TITLE, Style::Titlebar | Style::Close),
	playerTexture(LoadTextureFromPath("ShipSprite.psd")),
	asteroidTexture(LoadTextureFromPath("AsteroidSprite.psd")),
	coinTexture(LoadTextureFromPath("CoinSprite.psd")),
	gameIsOver(false),
	entityList(),
	asteroidTimer(0)
{

}

Game::~Game()
{
	while (!entityList.empty()) 
	{
		delete entityList.back();
		entityList.pop_back();
	}
}
;


void Game::Run() 
{
	//Create essential entities
	Player* player = new Player(VIDEO_MODE.width/2, VIDEO_MODE.height/2, VIDEO_MODE.width, VIDEO_MODE.height, PLAYER_RADIUS, "Player", PLAYER_SPEED_BASE, playerTexture);
	Coin* coin = new Coin(VIDEO_MODE.width / 2, 0, VIDEO_MODE.width, VIDEO_MODE.height, COIN_RADIUS, "Coin", COIN_SPEED_BASE, coinTexture);

	entityList.push_back(player);
	entityList.push_back(coin);

	//Ranomizer seed
	srand(std::time(NULL));

	//Frames
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
		gameWindow.clear(BACKGROUND_COLOR);
		AsteroidSpawner(deltaTime);
		EntityUpdate();
		EntityRender();
		CollisionManagement();
		EntityCleaner();
		if (CheckGameOverState(player, coin))
		{
			gameIsOver = true;
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

void Game::AsteroidSpawner(float deltaTime)
{
	//Spawn as many asteroids/s as the spawn rate allows
	if (asteroidTimer >= (1 / asteroid_spawn_rate)) 
	{
		//Reset timer
		asteroidTimer = 0;
	
		//Spawn a asteroid above window at random X
		int _spawnPosX = rand() % (VIDEO_MODE.width - ASTEROID_RADIUS) + ASTEROID_RADIUS;
		int _spawnPosY = 0 - ASTEROID_RADIUS;

		int _boundryX = VIDEO_MODE.width + ASTEROID_RADIUS;
		int _boundryY = VIDEO_MODE.height + ASTEROID_RADIUS;

		float _speed = 5;

		Asteroid* _asteroid = new Asteroid(_spawnPosX, _spawnPosY, _boundryX, _boundryY, ASTEROID_RADIUS, "Asteroid", _speed, asteroidTexture);


		entityList.push_back(_asteroid);
	}
	else
	{
		asteroidTimer += deltaTime;
	}

	//Increase spawn rate
	if (asteroid_spawn_rate <= ASTEROID_SPAWN_RATE_MAX) asteroid_spawn_rate += (ASTEROID_ACCELERATION_RATE * deltaTime);
}

bool Game::CheckGameOverState(Player* plyr, Coin* cn) 
{
	bool _output = false;

	if (plyr->markedDead || cn->markedDead) 
	{
		_output = true;
	}

	return _output;
}
