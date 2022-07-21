﻿//header files
#include<windows.h>
#include "Window.h"

#define ID_NUMBER 501

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[]=TEXT("WINDEV");

	//code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//creating the window
	hwnd = CreateWindow(szAppName, 
						TEXT("RVP: Window"), 
						WS_OVERLAPPEDWINDOW, 
						CW_USEDEFAULT, 
						CW_USEDEFAULT, 
						CW_USEDEFAULT,
						CW_USEDEFAULT, 
						NULL, 
						NULL, 
						hInstance, 
						NULL);

	//Show Window
	ShowWindow(hwnd, iCmdShow);

	///update window
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations
	HDC hdc; 
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hBrush; 
	static int iPaintFlag = 0;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_NUMBER, 1000, NULL);
		break;
	case WM_TIMER: 
		KillTimer(hwnd, ID_NUMBER);
		iPaintFlag++;
		if (iPaintFlag > 8)
		{
			iPaintFlag = 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, ID_NUMBER, 1000, NULL);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		if (iPaintFlag == 1)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
		}
		else if (iPaintFlag == 2)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (iPaintFlag == 3)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (iPaintFlag == 4)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (iPaintFlag == 5)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (iPaintFlag == 6)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (iPaintFlag == 7)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
		}
		else if (iPaintFlag == 8)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
		}
		else
		{
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
		}
		FillRect(hdc,&rc, hBrush);
		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
