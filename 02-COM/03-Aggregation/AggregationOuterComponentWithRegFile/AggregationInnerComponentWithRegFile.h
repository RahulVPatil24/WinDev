#pragma once
class IMultiplication:public IUnknown 
{
    public:
    virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};
class IDivision:public IUnknown
{
    public:
    virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;
};
                                            //{CEB4522B-7B68-4DB5-B00D-1094ED8FB421}
const CLSID CLSID_CMultiplicationDivision = {0xceb4522b, 0x7b68, 0x4db5, 0xb0, 0xd, 0x10, 0x94, 0xed, 0x8f, 0xb4, 0x21};

                                //{05FD2B85-22A8-4889-8529-39D6990FE6DE}
const IID IID_IMultiplication = {0x5fd2b85, 0x22a8, 0x4889, 0x85, 0x29, 0x39, 0xd6, 0x99, 0xf, 0xe6, 0xde};
                          
                          //{9299A90B-C356-43F0-A7F6-4E32D2BCDD97}
const IID IID_IDivision = {0x9299a90b, 0xc356, 0x43f0, 0xa7, 0xf6, 0x4e, 0x32, 0xd2, 0xbc, 0xdd, 0x97};
