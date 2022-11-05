class ISum :public IUnknown
{
public:
    virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};
class ISubtract : public IUnknown
{
public:
    virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
                                //{1BE63EC0-45B3-4B73-ABD6-669917FCCC2D}
const CLSID CLSID_CSumSubtract = {0x1be63ec0, 0x45b3, 0x4b73, 0xab, 0xd6, 0x66, 0x99, 0x17, 0xfc, 0xcc, 0x2d};

                     //{135E8449-9F5A-49A1-BC4F-6B778C942AA5}
const IID IID_ISum = {0x135e8449, 0x9f5a, 0x49a1, 0xbc, 0x4f, 0x6b, 0x77, 0x8c, 0x94, 0x2a, 0xa5};
                         
                          //{B437410B-710A-4749-81A4-344AB60A02BA}
const IID IID_ISubtract = {0xb437410b, 0x710a, 0x4749, 0x81, 0xa4, 0x34, 0x4a, 0xb6, 0xa, 0x2, 0xba};
