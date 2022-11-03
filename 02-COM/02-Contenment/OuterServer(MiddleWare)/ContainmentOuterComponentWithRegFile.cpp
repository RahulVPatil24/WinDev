#include<windows.h>
#include"ContainmentOuterComponentWithRegFile.h"
#include"ContainmentInnerComponentWithRegFile.h"

class CSumSubtract:public ISum,ISubtract,IMultiplication,IDivision
{
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	CSumSubtract(void);
	~CSumSubtract(void);
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractOfTwoIntegers(int, int, int*);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations 
long glNumberOfActiveComponents = 0; //numberof active components
long glnumberOfServerLocks = 0; //number if locks in this dll

//DllMain
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

//Implementation of CSumSubtract's Constructor Method 
CSumSubtract::CSumSubtract(void)
{
	//code 
	//initialization of private data members 
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //Increment global Counter
}

//Implementation of CSumSubtract's Destructor Method 
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}

//Implementation of CSumSubtract's IUnknown's Methods 
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	//code 
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract*>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication*>(this);
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
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
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
		return(0);
	}
	return(m_cRef);
}

//Implementataion of ISum's Methods 
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	//code 
	*pSum = num1 + num2;
	return(S_OK);
}

//Implementataion of ISubtract's Methods
HRESULT CSumSubtract::SubtractOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	//code 
	*pSubtract = num1 - num2;
	return(S_OK);
}

//Implementataion of IMultiplication's Methods 
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	//code 
	//delegate to inner component 
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return(S_OK);
}

//Implementation of IDivision's Methods 
HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	//code
	///delegate to inner component 
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	HRESULT hr;
	
	//code
	hr = CoCreateInstance(CLSID_CMultiplicationDivision, NULL, CLSCTX_INPROC_SERVER,  IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface Can Not Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}
	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface Can Not Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}
	return(S_OK);
}

//Implementation of CSumSubtractClassFactory's Constructor Method 
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef = 1; //Hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Implementation of CSumSubtractClassFactory's Destructor Method 
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
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
	return(m_cRef);
}

//Implementation Of CSumSubtractClassFactory's IClassFactory's Methods 
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void **ppv)
{
	//variable declaraations 
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	//code
	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}
	//Create the instance of component i.e of CSumSubtract class 
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
	{
		return(E_OUTOFMEMORY);
	}

	//initialize the inner component 
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize Inner Component"), TEXT("ERROR"), MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}

	//Get the requested interface 
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	//code
	if (fLock)
	{
		InterlockedIncrement(&glnumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glnumberOfServerLocks);
	}
	return(S_OK);
}

//Implementataion of Exported Function From This Dll 
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	CSumSubtractClassFactory *pCsumSubtractClassFactory = NULL;
	HRESULT hr;

	//code 
	if (rclsid != CLISD_CSumSubtract)
	{
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	//Create Class Factory 
	pCsumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCsumSubtractClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCsumSubtractClassFactory->QueryInterface(riid, ppv);
	pCsumSubtractClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code 
	if ((glNumberOfActiveComponents == 0) && (glnumberOfServerLocks == 0))
	{
		return(S_OK);
	}
	else
	{
		return(S_FALSE);
	}
}
