#include "Player.h"
#include <cmath>

Player::Player(int x, int y, int width, int height, float speed, HANDLE hndSprite)
{
	this->x= x;
	this->y = y;
	this->width = width;
	this->height=  height;
	this->speed = speed;
	angle = 0;
	GetObject(hndSprite, sizeof(BITMAP), &Bmp);
}

void Player::moveRight(float time)
{
	x += speed * time;
}

void Player::moveLeft(float time)
{
	x -= speed * time;
}

void Player::moveDown(float time)
{
	y += speed * time;
}

void Player::moveUp(float time)
{
	y -= speed * time;
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

void Player::drawPlayer(HWND hWnd, HANDLE hndSprite)
{
	HDC hdc = GetDC(hWnd);
	
	SetGraphicsMode(hdc, GM_ADVANCED);
	
	
	xform.eM11 = cos(angle);
	xform.eM12 = sin(angle);
	xform.eM21 = -sin(angle);
	xform.eM22 = cos (angle);
	xform.eDx = x;
	xform.eDy = y;
	SetWorldTransform(hdc, &xform);
	
	RECT rect;
	GetClientRect(hWnd, &rect);
	LPtoDP(hdc, (LPPOINT)&rect, 2);
	
	this->showBitmap(hdc, hndSprite);
	ReleaseDC(hWnd, hdc);
	
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

