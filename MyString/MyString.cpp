#include "stdafx.h"
#include "../MyString/MyString.h"
#include <iostream>
#include <stdlib.h>

CMyString::CMyString()
{
}

CMyString::CMyString(const char * pString)
{
}

CMyString::CMyString(const char * pString, size_t length)
{
}

CMyString::CMyString(const CMyString & other)
{
}

CMyString::CMyString(CMyString && other)
{
}

CMyString::CMyString(const std::string & stlString)
{
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
}

const char* CMyString::GetStringData() const
{
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
}

void CMyString::Clear()
{
}


