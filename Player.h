#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>

class Player
{
	RECT window;
	float speed;
	int x, y, width, height;
	float angle;  
	BITMAP Bmp;
	float scale;
	void showBitmap(HDC winDC, HANDLE hndSprite);
public:
	Player(int x, int y, int width, int height, float speed, HANDLE hndSprite, RECT window);
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
	void drawPlayer(HDC winDC, HWND hWnd, HANDLE hndSprite);
	void changeScale(float deltaScale);
	void checkForBorders(RECT window);
	void setWindow(RECT window);
};

#endif
