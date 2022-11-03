#include <windows.h>
#include "ContainmentInnerComponentWithRegFile.h"

//Class declarations 
class CMultiplicationDivision:public IMultiplication,IDivision
{
private: 
	long m_cRef;
public:
	//Constructor method declarations 
	CMultiplicationDivision(void);
	//Destructor method declarations 
	~CMultiplicationDivision(void);
	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//IMultiplication specific method declaration (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);
	//IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);
};
class CMultiplicationDivisionClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	//Constructor method declarations 
	CMultiplicationDivisionClassFactory(void);
	//Destructor mmethod declarations 
	~CMultiplicationDivisionClassFactory(void);
	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//IClassFactory specific method declarations (Inheriited)
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};
//global variable declaration 
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

//DLL Main
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

//Implement of CMultiplicationDivision's Constructor Method 
CMultiplicationDivision::CMultiplicationDivision(void)
{
	//code 
	m_cRef = 1; //Hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Implementation of CMultiplicationDivision's Destuctor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);//Decrement gloal counter.
}

//Implementation of CMultiplicationDivision's IUnknown's Methods 
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	//code 
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IMultiplication *>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication *>(this);
	}
	else if (riid == IID_IDivision)
	{
		*ppv = static_cast<IDivision*>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	} 
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release(void)
{
	//code 
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of IMultiplication's Methods 
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	//code
	*pMultiplication = num1*num2;
	return(S_OK);
}

//Implementation of IDivisoion's Methods 
HRESULT  CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}

//Implementation of CMultiplicationDivisionClassFactory's constructor Method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code 
	m_cRef = 1; //Hardcodede initialization to anticipate possible failure of QueryInterface()
}
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{

}

//Implementataion of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown Methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
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

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	//code 
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implement Of CMultiplicationDivisionClassFactory's IClassFactory's Methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	//variable declarations 
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}
	//Create the instance of component i.e of CMultiplicationDivision class 
	pCMultiplicationDivision = new CMultiplicationDivision;

	if (pCMultiplicationDivision == NULL)
	{
		return(E_OUTOFMEMORY);
	}

	//get the requested interface 
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release(); //anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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

//Implementation of Exported Functions From This Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr; 
	//code 
	if (rclsid != CLSID_CMultiplicationDivision)
	{
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	//Create Class Factory 
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	if (pCMultiplicationDivisionClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release(); //anticipate possible failure of QueryInterface()
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return(S_OK);
	}
	else
	{
		return(S_FALSE);
	}
}
