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
	const VideoMode videoMode = VideoMode(768, 1024);
	const Color backgroundColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;
}
#pragma endregion

Game::Game() :
	gameWindow(videoMode, windowTitle, Style::Titlebar | Style::Close),
	playerTexture(LoadTextureFromPath("ShipSprite.psd")),
	asteroidTexture(LoadTextureFromPath("AsteroidSprite.psd")),
	coinTexture(LoadTextureFromPath("CoinSprite.psd")),
	gameIsOver(false)
{

}

Game::~Game()
{
}
;


void Game::Run() 
{
	Player player(0, 0, 5, "Player", 5, playerTexture);

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

		//Clean-up
		gameWindow.clear(backgroundColor);
		player.Update();
		player.Render(gameWindow);
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