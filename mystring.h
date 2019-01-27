#pragma once
#include <stdexcept>
/*
1. Default ctor
2. Copy ctor
3. Move ctor
4. Copy assignment operator
5. Move assignment operator
6. Char* ctor
7. size
8. subscript operator
9. streaming operator
10. Dtor
*/
class MyString
{
public:
	MyString();
	MyString(const char* const rhs);
	MyString(const MyString& rhs);
	MyString(MyString&& rhs);
	MyString& operator=(const MyString& rhs);
	MyString& operator=(MyString&& rhs);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	size_t size() const;
	~MyString();
private:
	char* m_buffer;
};
