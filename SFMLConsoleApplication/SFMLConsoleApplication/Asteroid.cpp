#pragma once
#include "Asteroid.h"

Asteroid::Asteroid(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	dirY = 1; //1 == down, -1 == up
	ReadyGFX(texture);
};

Asteroid::~Asteroid() 
{
	UnloadGFX();
}

void Asteroid::ReadyGFX(sf::Texture* texture)
{
	//Set up a sprite with the provided texture and center it's origin

	mySprite = new sf::Sprite();
	mySprite->setTexture(*texture);

	float centerX = (mySprite->getLocalBounds().width / 2);
	float centerY = (mySprite->getLocalBounds().height / 2);

	mySprite->setOrigin(centerX, centerY);
}

void Asteroid::UnloadGFX()
{
	delete mySprite;
}

void Asteroid::MovementManagement() 
{
	//Move downwards
	//If below bottom while taken == false, asteroid dies

	int _dirY = dirY;

	posY += _dirY * moveSpeed;
	mySprite->setPosition(posX, posY);

	if (posY > (boundryY + (radius / 2)))
	{
		markedDead = true;
	}
}

void Asteroid::Update()
{
	MovementManagement();
}

void Asteroid::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(*mySprite);
}

void Asteroid::OnCollision(std::string CollisionId) 
{

}