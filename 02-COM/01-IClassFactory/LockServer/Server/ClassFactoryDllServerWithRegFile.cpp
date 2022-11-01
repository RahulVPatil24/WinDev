#include<Windows.h>
#include"ClassFactoryDllServerWithRegFile.h"


class CSumSubtract: public ISum, ISubtract 
{
private:
	//declaration
	long m_cRef;

public:
	//constructor
	CSumSubtract(void); 

	//Destructor
	~CSumSubtract(void);

	//Declarations of IUnknown methods 
	HRESULT __stdcall QueryInterface(REFIID, void **);
	
	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void);

	//iSum Method
	HRESULT __stdcall SumOfTwoIntigers(int, int, int *);

	//iSub Method
	HRESULT __stdcall SubOfTwoIntigers(int, int, int *);

};

// ClassFactory class

class CSumSubtractClassFactory: public IClassFactory
{
private: 
	long m_cRef;
public: 
	//constructor 
	CSumSubtractClassFactory(void);

	//destructor
	~CSumSubtractClassFactory(void);

	//Declarations of IUnknown methods 
	HRESULT __stdcall QueryInterface(REFIID, void **);

	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void);

	//iClass Factory methods
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};

//global variables 
long glNumberOfActiveComponents;
long glNumberOfServerLocks;
TCHAR str[255];

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	
	//Code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

//CSumSubtract implimentation 
//Constructor
CSumSubtract::CSumSubtract(void)
{
	//code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);

};

//Destructor 
CSumSubtract::~CSumSubtract()
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
};

//IUnknown Implimentations 
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum *>(this); 
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract *>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return (m_cRef);
}

//ISum Method Implimentation
HRESULT CSumSubtract::SumOfTwoIntigers(int num1, int num2, int *pSum)		//These function is just for an example. It can be encodeaudio
{
	//code
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubtract::SubOfTwoIntigers(int num1, int num2, int *pSubtract)	//These function is just for an example. It can be encodevideo
{
	//code
	*pSubtract = num1 - num2;
	return(S_OK);
}

//CSumSubtractClassFactoryImplimentation
//constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef = 1;
}

//destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}

//Iunknown methods implimentations
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
		if (m_cRef == 0)
		{
			delete(this);
			return(0);
		}
	return (m_cRef);
}

//ICLASSFactory MMETHODS IMPLIMENTATION
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations 
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
	{
		return(E_OUTOFMEMORY);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}

//lock server
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	//code
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return(S_OK);
}

//Exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	//variable declarations 
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_CSumSubtract)
	{
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		wsprintf(str, TEXT("Dll Is Not In Memory"));
		MessageBox(NULL, str, TEXT("MEMORY"), MB_OK);
		return(S_OK);
	}
	else
	{
		wsprintf(str, TEXT("Dll is in memory"));
		MessageBox(NULL, str, TEXT("MEMORY"), MB_OK);

		return(S_FALSE);
	}
}
