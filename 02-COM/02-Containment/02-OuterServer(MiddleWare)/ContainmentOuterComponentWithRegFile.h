#pragma once
class ISum :public IUnknown
{
public: 
	//ISum specific method declarations 
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};
class ISubtract :public IUnknown
{
public:
	//ISubtract specific method declarations 
	virtual HRESULT __stdcall SubtractOfTwoIntegers(int, int, int*) = 0;
};

//CLSID of SumSubtract Component {B75D4DBA-D4B6-4327-A5D8-4F02F2614192}
const CLSID CLISD_CSumSubtract = {0xb75d4dba, 0xd4b6, 0x4327, 0xa5, 0xd8, 0x4f, 0x2, 0xf2, 0x61, 0x41, 0x92};

//IID of ISum Interface {DDDF31D6-7AE4-4BE0-8ECA-25E5DE3DD696}
const IID IID_ISum = {0xdddf31d6, 0x7ae4, 0x4be0, 0x8e, 0xca, 0x25, 0xe5, 0xde, 0x3d, 0xd6, 0x96};

//IID of ISubtract Interface {FE6F81C8-F962-466B-98D4-BC381D582A2A}
const IID IID_ISubtract = {0xfe6f81c8, 0xf962, 0x466b, 0x98, 0xd4, 0xbc, 0x38, 0x1d, 0x58, 0x2a, 0x2a};
