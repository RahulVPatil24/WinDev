//header files
#include<windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//lONG __FAR__PASCAL WINDPROC (UINT,   UINT,  UINT, LONG); INTERNALLY TYPEDFS

//global variable declarations

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpszCmdLine, int iCmdShow)//unsigned int
{					
	//local variable declarations
	WNDCLASSEX wndclass;//struct
	HWND hwnd;
	MSG msg;//struct
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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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
	
	TCHAR str[255];
	int num1, num2, num3;

	//code
	switch (iMsg)
	{

	case WM_CREATE:	//WM means Window Messages
		num1 = 25;
		num2 = 75;
		num3 = num1 + num2;
		wsprintf(str, TEXT("sum of %d and %d is: %d"),num1, num2, num3);
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		break;

	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		break;

	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		break;

	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		break;

	/*case WM_SETFOCUS:
		wsprintf(str, TEXT("WM_SETFOCUS message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
																	// NANTAR 
		break;							
	case WM_KILLFOCUS:
		wsprintf(str, TEXT("WM_KILLFOCUS message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		break;*/
	
	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		PostQuitMessage(0);
		
		//PostMessage(HWND, WM_QUIT, 0, 0L);

		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
