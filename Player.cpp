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
	GetObject(hndSprite, sizeof(BITMAP), &Bmp);
}

void Player::moveRight(float time)
{
	int newX = x + speed * time;
	if(newX + width / 2 < window.right - window.left)
		x = newX;
}

void Player::moveLeft(float time)
{
	int newX = x - speed * time;
	if(newX - width / 2 > 0)
		x = newX;
}

void Player::moveDown(float time)
{
	int newY = y + speed * time;
	if(newY + height / 2 < window.bottom - window.top)
		y = newY;
}

void Player::moveUp(float time)
{
	int newY = y - speed * time;
	if(newY - height / 2 > 0)
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
	XFORM xform;
	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC hdc = memDC; 
	
	Gdiplus::Graphics graphics(hdc);
	
	
	showBitmap(hdc, hndSprite);
	
//	ReleaseDC(hWnd, hdc);
	
}

void Player::showBitmap(HDC winDC, HANDLE hndSprite)
{
	HDC memDC = CreateCompatibleDC(winDC);
    SelectObject(memDC, hndSprite);
	StretchBlt(winDC, -width / 2, -height / 2, width, height, memDC, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY); 
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

