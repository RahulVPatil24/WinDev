#include<windows.h>
#include<process.h>
#include "Window.h"
#include "HeaderForClientOfContainmentComponentWithRegFile.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[]=TEXT("WINDEV");
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
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//creating the window
	hwnd = CreateWindow(AppName, 
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
	//Function Declarations
	void SafeInterfaceRelease(void);

	//local variable declarations
	HRESULT hr;
	int iNum1, iNum2,iSum,iSubtraction, iMultiplication, iDivision;
	TCHAR str[255];

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLISD_CSumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 65;
		iNum2 = 45;

		//call SumOfTwoIntegers() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		//display the result 
		wsprintf(str, TEXT("Sum of %d And %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		//call QueryInterface() on ISum to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		//call QueryInterface() on ISubtract, to get IMultiplication's pointer
		iNum1 = 155;
		iNum2 = 55;

		pISubtract->SubtractOfTwoIntegers(iNum1, iNum2, &iSubtraction);
		wsprintf(str, TEXT("Subtraction Of %d And %d = %d"), iNum1, iNum2, iSubtraction);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not Be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISubtract->Release();
		pISubtract = NULL;

		iNum1 = 30;
		iNum2 = 25;

		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);
		wsprintf(str, TEXT("Multiplication of %d And %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 200;
		iNum2 = 25;

		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);
		wsprintf(str, TEXT("Division of %d And %d = %d"), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
	//code
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}
 