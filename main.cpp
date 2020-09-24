#include <windows.h>
#include <time.h>
#include <tchar.h>

#include "Player.h"

Player *ptrPlayer;

HDC hdcBack;
HBITMAP hbmBack;

HANDLE hndSprite;
void showBitmap(HWND hWnd, HANDLE hndSprite);

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	PAINTSTRUCT ps;
	static RECT rect;
	switch(Message) {		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_KEYDOWN:
		{
			GetClientRect(hWnd, &rect);
			int time = 10;
			switch (wParam) 
			{
				case VK_RIGHT:
					ptrPlayer->moveRight(time);
					break;
				case VK_LEFT:
					ptrPlayer->moveLeft(time);
					break;
				case VK_UP:
					ptrPlayer->moveUp(time);
					break;
				case VK_DOWN:
					ptrPlayer->moveDown(time);
					break;
				case VK_TAB:
					ptrPlayer->rotateRight(3.1415 / 180);
					break;
			}
			InvalidateRect(hWnd, &rect, false);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			short delta = HIWORD(wParam);
			short specialKeys = LOWORD(wParam);
			int time = 10;
			time = time * abs(delta) / 60;
			if(delta > 0)
			{
				if(specialKeys & MK_SHIFT)
					ptrPlayer->moveRight(time);
				else
					ptrPlayer->changeScale(delta / 100);
			}
			else if(delta < 0)
			{
				if(specialKeys & MK_SHIFT)
					ptrPlayer->moveLeft(time);
				else
					ptrPlayer->changeScale(delta /  100);
			}
			InvalidateRect(hWnd, &rect, false);
			break;
		}
		case WM_PAINT:
		{
			BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			hdcBack = CreateCompatibleDC(ps.hdc);
			hbmBack = CreateCompatibleBitmap(ps.hdc, rect.right - rect.left, 
				rect.bottom - rect.top);
			HBITMAP oldBmp = (HBITMAP)SelectObject(hdcBack, hbmBack);
			LOGBRUSH br;
			br.lbStyle = BS_SOLID;
			br.lbColor = 0xFFFFFF;
			HBRUSH brush;
			brush = CreateBrushIndirect(&br);
			SelectObject(hdcBack, brush);
			FillRect(hdcBack, &rect, brush);
			ptrPlayer->drawPlayer(hdcBack, hWnd, hndSprite);
			BitBlt(ps.hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, hdcBack, 0, 0, SRCCOPY);
		
			SelectObject(hdcBack, oldBmp);
			DeleteObject(hbmBack);
			DeleteDC(hdcBack);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_SIZE: 
		{
			if(ptrPlayer)
			{
				GetClientRect(hWnd, &rect);
				ptrPlayer->checkForBorders(rect);
				ptrPlayer->setWindow(rect);
				InvalidateRect(hWnd, NULL, false);
			}
			break;	
		}
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Laba1_OSiSP", WS_OVERLAPPEDWINDOW,
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
		
	RECT rect;
	GetClientRect(hwnd, &rect);
	ptrPlayer = new Player(50, 50, 50, 50, 0.4, hndSprite, rect);
	
	ShowWindow(hwnd, nCmdShow);
//	UpdateWindow(hwnd);

	MSG msg; 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}
