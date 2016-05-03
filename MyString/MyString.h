#pragma once
#include <string>
#include <sstream>

class CMyString
{
public:
	CMyString();
	CMyString(const char *pString);
	CMyString(const char *pString, size_t length);
	CMyString(const CMyString & other);
	CMyString(CMyString && other);
	CMyString(const std::string & stlString);

	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();
private:
	size_t m_length;
	char *m_pChars;
};