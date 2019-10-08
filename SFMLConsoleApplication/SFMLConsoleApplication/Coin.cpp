#pragma once
#include "Coin.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

Coin::Coin(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId) 
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	taken = false;
	dirY = 1; //1 == down, -1 == up
	ReadyGFX(texture);
};

Coin::~Coin()
{
	UnloadGFX();
}

void Coin::MovementManagement() 
{
	//Move downwards
	//If below bottom while taken == false, coin dies (game ends)

	int _dirY = dirY;

	posY += _dirY * moveSpeed;
	mySprite->setPosition(posX, posY);

	if (posY > (boundryY + (radius / 2))) 
	{
		markedDead = true;
	}
}

void Coin::OnCollision(std::string CollisionId) 
{
	//If hit by player, teleport to new position on top of screen
	if (CollisionId == "Player") 
	{
		markedDead = false;
		Teleport();
	}
}

void Coin::ReadyGFX(sf::Texture* texture)
{
	//Set up a sprite with the provided texture and center it's origin

	mySprite = new Sprite();
	mySprite->setTexture(*texture);

	float centerX = (mySprite->getLocalBounds().width / 2);
	float centerY = (mySprite->getLocalBounds().height / 2);

	mySprite->setOrigin(centerX, centerY);
}

void Coin::UnloadGFX()
{
	delete mySprite;
}

void Coin::Teleport() 
{
	posX = (rand() % (int)(boundryX - (radius / 2)));
	posY = (0 - (radius / 2) - boundryY);
}

void Coin::Update()
{
	MovementManagement();
}

void Coin::Render(RenderWindow& renderWindow)
{
	renderWindow.draw(*mySprite);
}