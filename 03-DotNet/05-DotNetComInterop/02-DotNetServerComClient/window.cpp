#include<windows.h>
#include "Window.h"

#import "DotNetServer.tlb" no_namespace named_guids raw_interfaces_only /*.net ne tayaar keleli (regasm ne tayaar keleli) import kar .net ne tayaar keleli tlb
																		pan me cpp ahe tyaamule malaa ti majhyaa language madhe pahije mhanun tujhe namespaces 
																		waapru nako== nonamespce, named guids waapar unamed waapru nakos == named_guids 
																		tuze interfaces malaa nakot malaa fakta maajhe iUnknown madhun aalelet interfaces pahijet 
																		Mhanhech raw interfaces pahije malaa == raw_interfaces_only*/

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
	IDispatch* pIDispatch = NULL;
	HRESULT hr;
	//OLECHAR* is also called as bstr which stands for binary string
	OLECHAR* szFunctionName1 = L"SumOfTwoIntegers"; // Here L means OLE Character Literal(literal means pure string)
	OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2];
	VARIANT vResult;
	DISPID dispid;
	DISPPARAMS params;
	int n1, n2, sum, subtract;
	TCHAR str[255];

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("CoInitialize Failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = CoCreateInstance(CLSID_DotNetServer, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("CoCreateInstance Failed To Get IDispatch Interface"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 275;
		n2 = 225;
		
		//Get ID of SumOfTwoIntegers
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName1, 1, GetUserDefaultLCID(), &dispid);

		if (FAILED(hr))
		{
			wsprintf(str, TEXT("GetIDsOfNames Failed To Give ID Of SumOfTwoIntegers"));
			MessageBox(hwnd, str, TEXT("SUM"), MB_OK);
			pIDispatch->Release();
			pIDispatch = NULL;
			DestroyWindow(hwnd);
		}

		//Call SumOfTwoIntegers By Passing It's ID Two Invoke

		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = n2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = n1;

		VariantInit(&vResult);

		params.rgvarg = vArg;
		params.cArgs = 2;
		params.rgdispidNamedArgs = NULL;
		params.cNamedArgs = 0;

		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vResult, NULL, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Cannot Invoke function."), TEXT("Program Error"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		
		sum = vResult.lVal;
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, sum);
		MessageBox(hwnd, str, TEXT("SumOfTwoIntegers"), MB_OK);

		//Get IDs Of SubtractionOfTwoIntegers
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);

		if (FAILED(hr))
		{
			wsprintf(str, TEXT("GetIDsOfNames Failed To Give ID Of SubtractionOfTwoIntegers"));
			MessageBox(hwnd, str, TEXT("SUM"), MB_OK);
			pIDispatch->Release();
			pIDispatch = NULL;
			DestroyWindow(hwnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vResult, NULL, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Cannot Invoke function."), TEXT("Program Error"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		subtract = vResult.lVal;
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, subtract);
		MessageBox(hwnd, str, TEXT("SubtractionofTwoIntegers"), MB_OK);

		VariantClear(&vResult);
		VariantClear(vArg);
		
		pIDispatch->Release();
		pIDispatch = NULL;

		break;
	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
 