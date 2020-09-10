#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>

class Player
{
	float speed;
	int x, y, width, height;
	float angle;  
	XFORM xform;
	BITMAP Bmp;
	void showBitmap(HDC winDC, HANDLE hndSprite);
public:
	Player(int x, int y, int width, int height, float speed, HANDLE hndSprite);
	void moveRight(float time);
	void moveLeft(float time);
	void moveUp(float time);
	void moveDown(float time);
	void rotateRight(float deltaAngle);
	void rotateLeft(float deltaAngle);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	void drawPlayer(HWND hWnd, HANDLE hndSprite);
};

#endif
