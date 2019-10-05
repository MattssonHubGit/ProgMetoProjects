#pragma once
#include "Asteroid.h"

Asteroid::Asteroid(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, int iniDirX, int iniDirY, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	dirX = iniDirX;
	dirY = iniDirY;
	ReadyGFX(texture);
};

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

}

void Asteroid::Update()
{

}

void Asteroid::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(*mySprite);
}

void Asteroid::OnCollision(std::string CollisionId) 
{

}