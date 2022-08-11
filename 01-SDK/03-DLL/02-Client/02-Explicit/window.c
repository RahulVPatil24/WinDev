//header files
#include<windows.h>
#include "Window.h"

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
	HMODULE hDll = NULL;
	typedef int (*MakeCubeFunctionPointer)(int);
	MakeCubeFunctionPointer pflMakeCube = NULL;
	int iNum = 5;
	int iCube; 
	TCHAR str[255];
		
	//code
	switch (iMsg)
	{
	case WM_CREATE:

		hDll = LoadLibrary(TEXT("MyMathTwo.dll"));
		if (hDll == NULL)
		{
			MessageBox(hwnd, TEXT("LoadLibrary()failed"), TEXT("ERROR"),MB_OK);
			DestroyWindow(hwnd);
		}

		pflMakeCube = (MakeCubeFunctionPointer)GetProcAddress(hDll, "MakeCube");
		if (pflMakeCube == NULL)
		{
			MessageBox(hwnd, TEXT("GetProcAddress()failed"), TEXT("ERROR"),MB_OK);
			FreeLibrary(hDll);
			DestroyWindow(hwnd);
		}
		iCube = pflMakeCube(iNum);
		wsprintf(str, TEXT("Cube of %d is: %d"), iNum, iCube);
		MessageBox(hwnd, str, TEXT("Cube"), MB_OK);

		FreeLibrary(hDll);
		hDll = NULL;
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
