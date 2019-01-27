#include "mystring.h"
#include <string.h>
#include <stdexcept>

MyString::MyString()
	:m_buffer{new char[1]}
{
	m_buffer[0] = '\0';
}

MyString::MyString(const char* const rhs)
	:m_buffer{_strdup(rhs)}
{
	if (!m_buffer)
		throw std::invalid_argument{ "Source pointer is invalid" };
}

MyString::MyString(const MyString& rhs)
	:m_buffer{ _strdup(rhs.m_buffer) }
{
	if (!m_buffer)
		throw std::invalid_argument{ "Source pointer is invalid" };
}

MyString::MyString(MyString&& rhs)
	:m_buffer{rhs.m_buffer}
{
	rhs.m_buffer = nullptr;
}
//Copy and swap is expensive when assigning to self. Safe but expensive.
//deleting m_buffer before allocating will not be exception safe if the allocation throws bad_alloc exception.
MyString& MyString::operator=(const MyString& rhs)
{
	if (this == &rhs)
		return *this;

	auto tmp = m_buffer;
	m_buffer = _strdup(rhs.m_buffer);
	delete tmp;
	return *this;
}

MyString& MyString::operator=(MyString&& rhs)
{
	if (this == &rhs)
		return *this;

	auto tmp = m_buffer;
	m_buffer = rhs.m_buffer;
	delete tmp;
	return *this;
}

const char& MyString::operator[](size_t index) const
{
	if (index >= size())
		throw std::out_of_range{"Index out of bounds"};

	return m_buffer[index];
}

//Implement in terms of the const version to avoid duplication
char& MyString::operator[](size_t index)
{
	return const_cast<char&>(static_cast<const MyString&>(*this)[index]);
}

//Size should be O(1) but this version is O(n)
size_t MyString::size() const
{
	return strlen(m_buffer);
}

MyString::~MyString()
{
	delete m_buffer;
}