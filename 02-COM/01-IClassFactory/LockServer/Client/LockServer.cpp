//header files
#include<windows.h>
#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"

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
	TCHAR szAppName[] = TEXT("WINDEV");
	HRESULT hr;

	//code
	// COM LIBRARY INITIALIZATION

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM initialization fialed"), TEXT("ERROR"), MB_OK);
		exit(0);
	}

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

	//COM uninitialization
	CoUninitialize();

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations
	IClassFactory* pIClassFactory = NULL;
	ISum* pISum = NULL;
	ISubtract* pISubtract = NULL;
	HRESULT hr;
	int n1, n2, sum, subtract;
	TCHAR str[255];
	n1 = 55;
	n2 = 45;
	//code
	switch (iMsg)
	{
	case WM_CREATE:


		/*do
		{
			if (pIClassFactory)
			{
				pIClassFactory->Release();
			}
			hr = CoGetClassObject(CLSID_CSumSubtract, CLSCTX_INPROC_SERVER, 0, IID_IClassFactory, (void**)&pIClassFactory);
			if (FAILED(hr))
			{
				return(E_NOINTERFACE);
				break;
			}
			pIClassFactory->CreateInstance(NULL, IID_ISum, (void**)&pISum);
			pIClassFactory->LockServer(TRUE);
			pIClassFactory->Release();

			pISum->SumOfTwoIntigers(n1, n2, &sum);
			wsprintf(str, TEXT("Sum of %d and %d is: %d"), n1, n2, sum);
			MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

			pISum->Release();
			
		} while (FAILED(hr));*/

		
		hr = CoGetClassObject(CLSID_CSumSubtract, CLSCTX_INPROC_SERVER, 0, IID_IClassFactory, (void**)&pIClassFactory);

		if (SUCCEEDED(hr))
		{
			pIClassFactory->CreateInstance(NULL, IID_ISum, (void**)&pISum);
			pIClassFactory->LockServer(TRUE);
			pIClassFactory->Release();

			//pIClassFactory->LockServer(FALSE);
			pISum->SumOfTwoIntigers(n1, n2, &sum);
			wsprintf(str, TEXT("Sum of %d and %d is: %d"), n1, n2, sum);
			MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

			pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

			pISubtract->SubOfTwoIntigers(n1, n2, &subtract);
			wsprintf(str, TEXT("Subtraction of %d and %d is: %d"), n1, n2, subtract);
			MessageBox(hwnd, str, TEXT("Subtract"), MB_OK);
		}

		if (pISubtract)
		{
			pISubtract->Release();
			pISubtract = NULL;
		}
		if (pISum)
		{
			pISum->Release();
			pISum = NULL;
		}

		Sleep(7000);

		hr = CoGetClassObject(CLSID_CSumSubtract, CLSCTX_INPROC_SERVER, 0, IID_IClassFactory, (void**)&pIClassFactory);

		if (SUCCEEDED(hr))
		{

			pIClassFactory->CreateInstance(NULL, IID_ISum, (void**)&pISum);

			pISum->SumOfTwoIntigers(n1, n2, &sum);
			wsprintf(str, TEXT("Sum of %d and %d is: %d"), n1, n2, sum);
			MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

			pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

			pISubtract->SubOfTwoIntigers(n1, n2, &subtract);
			wsprintf(str, TEXT("Subtraction of %d and %d is: %d"), n1, n2, subtract);
			MessageBox(hwnd, str, TEXT("Subtract"), MB_OK);
		}

		if (pISubtract)
		{
			pISubtract->Release();
			pISubtract = NULL;
		}
		if (pISum)
		{
			pISum->Release();
			pISum = NULL;
		}
			
		//pIClassFactory->LockServer(FALSE);

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
