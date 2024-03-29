//header files
#include<windows.h>
#include "Window.h"
#include "MyMathOne.h"

#pragma comment(lib, "MyMathOne.lib")

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

	int iNum = 5;
	int iSquare;
	TCHAR str[255];

	//code
	switch (iMsg)
	{
	case WM_CREATE:

		iSquare = MakeSquare(iNum);
		wsprintf(str, TEXT("Square of %d is: %d"), iNum, iSquare);
		MessageBox(hwnd,str, TEXT("CALCULATION OF SQUARE"),MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
