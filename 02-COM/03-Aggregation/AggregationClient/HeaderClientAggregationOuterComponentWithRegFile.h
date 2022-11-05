class ISum:public IUnknown
{
public:
	//ISum specific method declarations 
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};
class ISubtract:public IUnknown
{
public:
	//ISubtract specific method declarations 
	virtual HRESULT __stdcall SubtractOfTwoIntegers(int, int, int*) = 0;
};
class IMultiplication:public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};
class IDivision:public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

//CLSID of SumSubtract Component {1BE63EC0-45B3-4B73-ABD6-669917FCCC2D}
const CLSID CLISD_CSumSubtract = {0x1be63ec0, 0x45b3, 0x4b73, 0xab, 0xd6, 0x66, 0x99, 0x17, 0xfc, 0xcc, 0x2d};

//IID of ISum Interface {135E8449-9F5A-49A1-BC4F-6B778C942AA5}
const IID IID_ISum = {0x135e8449, 0x9f5a, 0x49a1, 0xbc, 0x4f, 0x6b, 0x77, 0x8c, 0x94, 0x2a, 0xa5};

//IID of ISubtract Interface {B437410B-710A-4749-81A4-344AB60A02BA}
const IID IID_ISubtract = {0xb437410b, 0x710a, 0x4749, 0x81, 0xa4, 0x34, 0x4a, 0xb6, 0xa, 0x2, 0xba};

//IID of IMultiplication Interface {05FD2B85-22A8-4889-8529-39D6990FE6DE}
const IID IID_IMultiplication = {0x5fd2b85, 0x22a8, 0x4889, 0x85, 0x29, 0x39, 0xd6, 0x99, 0xf, 0xe6, 0xde};

//IID of IDivision Interface {9299A90B-C356-43F0-A7F6-4E32D2BCDD97}
const IID IID_IDivision = {0x9299a90b, 0xc356, 0x43f0, 0xa7, 0xf6, 0x4e, 0x32, 0xd2, 0xbc, 0xdd, 0x97};
