#include "Player.h"
#include <cmath>

Player::Player(int x, int y, int width, int height, float speed, HANDLE hndSprite, RECT window)
{
	this->x= x;
	this->y = y;
	this->width = width;
	this->height=  height;
	this->speed = speed;
	this->window = window;
	angle = 0;
	scale = 1;
	GetObject(hndSprite, sizeof(BITMAP), &Bmp);
}

void Player::moveRight(float time)
{
	int newX = x + speed * time;
	if(newX + width * scale/ 2 < window.right - window.left)
		x = newX;
}

void Player::moveLeft(float time)
{
	int newX = x - speed * time;
	if(newX - width * scale / 2 > 0)
		x = newX;
}

void Player::moveDown(float time)
{
	int newY = y + speed * time;
	if(newY + height * scale/ 2 < window.bottom - window.top)
		y = newY;
}

void Player::moveUp(float time)
{
	int newY = y - speed * time;
	if(newY - height * scale / 2 > 0)
		y = newY;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

void Player::drawPlayer(HDC memDC, HWND hWnd, HANDLE hndSprite)
{		
	showBitmap(memDC, hndSprite);
	
//	ReleaseDC(hWnd, hdc);
	
}

void Player::showBitmap(HDC winDC, HANDLE hndSprite)
{
	HDC memDC = CreateCompatibleDC(winDC);
    SelectObject(memDC, hndSprite);
	StretchBlt(winDC, x - width * scale / 2, y - height *scale / 2, 
		width * scale, height * scale, memDC, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY); 
	DeleteDC(memDC); 
}

void Player::rotateRight(float deltaAngle)
{
	angle += deltaAngle;
}

void Player::rotateLeft(float deltaAngle)
{
	angle -= deltaAngle;
}

void Player::changeScale(float deltaScale)
{
	this->scale += deltaScale;
	if(scale < 1)
		scale = 1;
}

void Player::checkForBorders(RECT window)
{
	if(x + width * scale / 2 > window.right)
		x = window.right - width / 2;
	if(x - width * scale/ 2 < 0)
		x = width / 2;
	if(y + height * scale / 2 > window.bottom)
		y = window.bottom - height / 2;
	if(y - height * scale / 2 < 0)
		y = height / 2;
}

void Player::setWindow(RECT window)
{
	this->window = window;
}

