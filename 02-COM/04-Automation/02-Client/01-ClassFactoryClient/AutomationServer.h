class IMyMath :public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};						//{B8EEC560-CB18-4FCA-B84C-ECC676E7BE85}
const CLSID CLSID_MyMath = {0xb8eec560, 0xcb18, 0x4fca, 0xb8, 0x4c, 0xec, 0xc6, 0x76, 0xe7, 0xbe, 0x85};

						//{F2FD02FB-7DB1-4622-875D-5128B3885E96}
const IID IID_IMyMath = {0xf2fd02fb, 0x7db1, 0x4622, 0x87, 0x5d, 0x51, 0x28, 0xb3, 0x88, 0x5e, 0x96};
