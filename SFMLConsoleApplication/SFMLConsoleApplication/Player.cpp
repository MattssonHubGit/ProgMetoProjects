#include "Player.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

Player::Player(int iniX, int iniY, float iniRad, std::string colId, float speed, Texture* texture) : Entity(iniX, iniY, iniRad, colId) {
	moveSpeed = speed;
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

	//posX += _xInput * moveSpeed;
	//posY += _yInput * moveSpeed;

	mySprite->move(_xInput * moveSpeed, _yInput * moveSpeed);
}

void Player::ReadyGFX(sf::Texture *texture) 
{
	mySprite = new Sprite();

	mySprite->setTexture(*texture);
	mySprite->setTextureRect(IntRect(9, 14, 64, 64));
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
