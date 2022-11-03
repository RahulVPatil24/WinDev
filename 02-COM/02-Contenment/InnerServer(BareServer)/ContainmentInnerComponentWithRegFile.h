#pragma once
class IMultiplication:public IUnknown
{
public: 
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *)=0;
};
class IDivision:public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *)=0;
};


//CLSID MultiplicationDivision Component {9E991280-D228-4C9C-9DA0-90FBF6A0ED24}
const CLSID CLSID_CMultiplicationDivision = {0x9e991280, 0xd228, 0x4c9c, 0x9d, 0xa0, 0x90, 0xfb, 0xf6, 0xa0, 0xed, 0x24};

//IID of IMultiplication Interface {58BC5249-CB81-471C-9A0D-998CE534D5CF}
const IID IID_IMultiplication = {0x58bc5249, 0xcb81, 0x471c, 0x9a, 0xd, 0x99, 0x8c, 0xe5, 0x34, 0xd5, 0xcf};

//IID of IDivision Interface {675DE2D1-AC89-44CB-AEA4-947327D4B2E2}
const IID IID_IDivision = {0x675de2d1, 0xac89, 0x44cb, 0xae, 0xa4, 0x94, 0x73, 0x27, 0xd4, 0xb2, 0xe2};
 