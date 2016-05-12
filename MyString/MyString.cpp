#include "stdafx.h"
#include <assert.h>
#include "MyString.h"

CMyString::CMyString()
	: CMyString("", 0)
{
}

CMyString::CMyString(const std::string & stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::CMyString(const char * pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char * pString, size_t length)
	: m_length(length)
{
	Create();
	std::memcpy(m_first, pString, m_length);
}

CMyString::CMyString(const CMyString & other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString && other)
	: m_first(other.m_first)
	, m_length(other.m_length)
{
	other.Clear();
}

CMyString::~CMyString()
{
	delete[] m_first;
}

void CMyString::Create()
{
	m_first = new char[m_length + 1];
	m_first[m_length] = '\0';
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_first;
}

const CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (m_length > 0 && start < m_length && length <= m_length && start < length)
	{
		return CMyString(&m_first[start], length);
	}
	return CMyString();
}

void CMyString::Clear()
{
	delete[] m_first;
	m_length = 0;
	Create();
}

CMyString & CMyString::operator +=(const CMyString & str)
{
	if (str.m_length > 0)
	{
		auto tempStr = new char[m_length + str.GetLength() + 1];
		tempStr[m_length + str.GetLength()] = '\0';
		memcpy(tempStr, m_first, m_length);
		memcpy(tempStr + m_length, str.m_first, str.m_length);
		delete[] m_first;
		m_length += str.m_length;
		m_first = tempStr;
	}
	return *this;
}

const CMyString operator +(const CMyString & lhs, const CMyString & rhs)
{
	return (CMyString(lhs) += rhs);
}

const CMyString operator +(const std::string & lhs, const CMyString & rhs)
{
	return (CMyString(lhs) += rhs);
}

const CMyString operator +(const char* lhs, const CMyString & rhs)
{
	return (CMyString(lhs) += rhs);
}

bool const operator !=(const CMyString & lhs, const CMyString & rhs)
{
	return !(lhs == rhs);
}

const bool operator <(const CMyString & lhs, const CMyString & rhs)
{
	if (lhs.GetLength() < rhs.GetLength())
	{
		return true;
	}
	else if (lhs.GetLength() > rhs.GetLength())
	{
		return false;
	}
	else
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) < 0;
	}
}

const bool operator >(const CMyString & lhs, const CMyString & rhs)
{
	if (lhs.GetLength() > rhs.GetLength())
	{
		return true;
	}
	else if (lhs.GetLength() < rhs.GetLength())
	{
		return false;
	}
	else
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) > 0;
	}
}

const bool operator <=(const CMyString & lhs, const CMyString & rhs)
{
	return !(lhs > rhs);
}

const bool operator >=(const CMyString & lhs, const CMyString & rhs)
{
	return !(lhs < rhs);
}

bool const operator ==(const CMyString & lhs, const CMyString & rhs)
{
	return (lhs.GetLength() == rhs.GetLength()) && (0 == std::memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()));
}

CMyString & CMyString::operator =(CMyString && other)
{
	if (this != &other)
	{
		std::swap(m_first, other.m_first);
		std::swap(m_length, other.m_length);
		other.Clear();
	}
	return *this;
}

CMyString & CMyString::operator =(const CMyString & other)
{
	if (this != &other)
	{
		Clear();
		*this = CMyString(other);
	}
	return *this;
}

char & CMyString::operator [](size_t pos)
{
	// TODO: fix bounds check. Example:
	//	 CMyString str("abc");
	//	 str[3] = "d";
	//	 std::cout << str << std::endl;

	assert(pos < m_length);
	return m_first[pos];
}

const char & CMyString::operator [](size_t pos) const
{
	assert(pos <= m_length);
	return m_first[pos];
}

std::istream & operator >>(std::istream & strm, CMyString & str)
{
	std::string string;
	if (strm >> string) // TODO: fix case when reading failed
	{
		str = string;
	}
	return strm;
}

std::ostream & operator <<(std::ostream & strm, const CMyString & str)
{
	auto string = str.GetStringData();
	for (size_t i = 0; i < str.GetLength(); i++)
	{
		if (string[i] != '\0')
		{
			strm << string[i];
		}
	}
	 // TODO: fix printing strings with '\0'
	return strm;
}