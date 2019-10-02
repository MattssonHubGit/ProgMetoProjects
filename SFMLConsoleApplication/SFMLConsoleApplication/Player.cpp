#pragma once
#include "Player.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

Player::Player(int iniX, int iniY, int boundX, int boundY, float iniRad, std::string colId, float speed, Texture* texture) : Entity(iniX, iniY, iniRad, colId) 
{
	moveSpeed = speed;
	boundryX = boundX;
	boundryY = boundY;
	ReadyGFX(texture);
};

Player::~Player() 
{
	UnloadGFX();
}

void Player::OnCollision(std::string CollisionId) 
{

}

void Player::MovementManagement() 
{
	//Input
	int _xInput = 0;
	int _yInput = 0;

		//Horizontal
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		_xInput++;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		_xInput--;
	}

		//Vertical
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		_yInput--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		_yInput++;
	}

	//Output
	posX += _xInput * moveSpeed;
	posY += _yInput * moveSpeed;

	//Boundries
	if (posX > (boundryX - (radius / 2))) posX = (boundryX - (radius / 2));
	if (posY > (boundryY - (radius / 2))) posY = (boundryY - (radius / 2));
	if (posX < (0 + (radius / 2))) posX = 0 + (radius / 2);
	if (posY < (0 + (radius / 2))) posY = 0 + (radius / 2);

	//Execute
	mySprite->setPosition(posX, posY);
}

void Player::ReadyGFX(sf::Texture *texture) 
{
	//Set up a sprite with the provided texture and center it's origin

	mySprite = new Sprite();
	mySprite->setTexture(*texture);

	float centerX = (mySprite->getLocalBounds().width / 2);
	float centerY = (mySprite->getLocalBounds().height / 2);

	mySprite->setOrigin(centerX, centerY);
}

void Player::UnloadGFX() 
{
	delete mySprite;
}

void Player::Update() 
{
	MovementManagement();
}

void Player::Render(RenderWindow &renderWindow) 
{
	renderWindow.draw(*mySprite);
}
