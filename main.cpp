#include <windows.h>
#include <time.h>
#include <tchar.h>

#include "Player.h"

const int UPDATE_INTERVAL = 40;

float speed = 0.05;
int timeForFrame = 40;
int ellapsedTime;
Player *ptrPlayer;
char *keyUpText = "Up";
char *keyDownText = "Down";
char *keyLeftText = "Left";
char *keyRightText = "Right";
char *lastKeyText = "None";

HDC hdcBack;
HBITMAP hbmBack;

HANDLE hndSprite;
void showBitmap(HWND hWnd, HANDLE hndSprite);

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	PAINTSTRUCT ps;
	static RECT rect;
	switch(Message) {
		case WM_CREATE:
		{
			GetWindowRect(hWnd, &rect);
			HDC hdc = GetDC(hWnd);
			hdcBack = CreateCompatibleDC(hdc);
			hbmBack = CreateCompatibleBitmap(hdc, rect.right - rect.left, 
				rect.bottom - rect.top);
			break;
		}
		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_KEYDOWN:
		{
			int time = ellapsedTime > UPDATE_INTERVAL ? UPDATE_INTERVAL : ellapsedTime;
			switch (wParam) 
			{
				case VK_RIGHT:
					ptrPlayer->moveRight(time);
					lastKeyText = keyRightText;
					break;
				case VK_LEFT:
					ptrPlayer->moveLeft(time);
					lastKeyText = keyLeftText;
					break;
				case VK_UP:
					ptrPlayer->moveUp(time);
					lastKeyText = keyUpText;
					break;
				case VK_DOWN:
					ptrPlayer->moveDown(time);
					lastKeyText = keyDownText;
					break;
				case VK_TAB:
					ptrPlayer->rotateRight(3.1415 / 180);
					break;
			}
			break;
		//	MoveWindow(hWnd, x, y, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		}
		case WM_MOUSEWHEEL:
		{
			short delta = HIWORD(wParam);
			short specialKeys = LOWORD(wParam);
			int time = ellapsedTime > UPDATE_INTERVAL ? UPDATE_INTERVAL : ellapsedTime;
			time = time * abs(delta) / 60;
			if(delta > 0)
			{
				if(specialKeys & MK_SHIFT)
					ptrPlayer->moveRight(time);
				else
					ptrPlayer->moveUp(time);
			}
			else if(delta < 0)
			{
				if(specialKeys & MK_SHIFT)
					ptrPlayer->moveLeft(time);
				else
					ptrPlayer->moveDown(time);
			}
			break;
		}
		case WM_PAINT:
		{
			BeginPaint(hWnd, &ps);
			LOGBRUSH br;
			br.lbStyle = BS_SOLID;
			br.lbColor = 0xEECCCC;
			HBRUSH brush;
			brush = CreateBrushIndirect(&br);
			SelectObject(ps.hdc, brush);
			Rectangle(ps.hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom);
			RECT textRect{155, 0, 300, 150};
			DrawText(ps.hdc, lastKeyText, -1, &textRect, DT_CENTER);
			ptrPlayer->drawPlayer(hWnd, hndSprite);
			EndPaint(hWnd, &ps);
			break;
		}
		
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}

void showBitmap(HWND hWnd, HANDLE hndSprite) 
{
	HDC winDC = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(winDC);
	BITMAP Bmp;
	GetObject(hndSprite, sizeof(BITMAP), &Bmp);
    SelectObject(memDC, hndSprite);
	StretchBlt(winDC, 0, 0, 64, 64, memDC, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY); 
    DeleteDC(memDC);
    ReleaseDC(hWnd, winDC);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; 

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	HWND hwnd; 
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		640, 
		480, 
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) { 
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hndSprite = LoadImage(NULL, "food.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(hndSprite == NULL)
	{
		MessageBox(NULL, "Bitmap loading failed!", "Error!", MB_OK);
	}
	
	ptrPlayer = new Player(50, 50, 50, 50, speed, hndSprite);

	MSG msg; 
	int accumulatedTime = 0;
	int tm1 = clock();
	int tm2;
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		tm2 = clock();
		ellapsedTime = tm2 - tm1;
		accumulatedTime += ellapsedTime;
		tm1 = tm2;
		if(accumulatedTime >= timeForFrame) 
		{
			InvalidateRect(hwnd, NULL, FALSE);
			accumulatedTime -= timeForFrame;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}
