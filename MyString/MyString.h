#pragma once

class CMyString
{
public:
	CMyString();
	CMyString(const char * pString);
	CMyString(const char * pString, size_t length);
	CMyString(const CMyString & other);
	CMyString(CMyString && other);
	CMyString(const std::string & stlString);

	~CMyString();

	size_t GetLength() const;
	const char * GetStringData() const;
	const CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString & operator =(CMyString const & other);
	CMyString & operator =(CMyString && other);
	char & operator [](size_t pos);
	char const & operator [](size_t pos) const;
	CMyString & operator +=(const CMyString & other);

private:
	void Delete();
	void Create(size_t length);

	char * m_first;
	size_t m_length;

};

const CMyString operator +(const CMyString &lhs, const CMyString &rhs);
const CMyString operator +(const std::string &lhs, const CMyString &rhs);
const CMyString operator +(const char* lhs, const CMyString &rhs);

const bool operator ==(const CMyString &str1, const CMyString &str2);
const bool operator !=(const CMyString & str1, const CMyString & str2);

const bool operator <(const CMyString &str1, const CMyString &str2);
const bool operator >(const CMyString &str1, const CMyString &str2);
const bool operator <=(const CMyString &str1, const CMyString &str2);
const bool operator >=(const CMyString &str1, const CMyString &str2);

std::istream & operator >> (std::istream & strm, CMyString & str);
std::ostream & operator<< (std::ostream & strm, CMyString const& str);