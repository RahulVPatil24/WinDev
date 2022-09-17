#pragma once
class ISum:public IUnknown
{
public: 
	virtual HRESULT __stdcall SumOfTwoIntigers(int, int, int *)=0;
};

class ISubtract:public IUnknown
{
public:
	virtual HRESULT __stdcall SubOfTwoIntigers(int, int, int *)=0; 
};

// // {085CF1FF-8328-4823-BAB8-5E613A1A2E8E}
const CLSID CLSID_CSumSubtract = {0x85cf1ff, 0x8328, 0x4823, 0xba, 0xb8, 0x5e, 0x61, 0x3a, 0x1a, 0x2e, 0x8e}; 

// {027CFB7B-5748-43A3-AFA0-6146D00E6500}
const IID IID_ISum = {0x27cfb7b, 0x5748, 0x43a3, 0xaf, 0xa0, 0x61, 0x46, 0xd0, 0xe, 0x65, 0x0};

// {1C6CCDE5-7CD3-4384-9E5C-7146CE35771A}
const IID IID_ISubtract = {0x1c6ccde5, 0x7cd3, 0x4384, 0x9e, 0x5c, 0x71, 0x46, 0xce, 0x35, 0x77, 0x1a};
