#pragma once
#include <initializer_list>
#include <algorithm>
/*
1. Lets sort out the typedefs
2. Constructors - default, copy, move, initialiser list, range, fill - takes a count and an element.
*/
template <typename T>
class MyVector
{
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	MyVector();
	MyVector(const MyVector& other);
	MyVector(MyVector&& other);
	MyVector(const std::initializer_list<value_type> list);
	MyVector(size_t n, const value_type& value = value_type{});
private:
	T* m_data;
	size_type m_size;
};

template <typename T>
MyVector::MyVector()
	:m_data{nullptr},
	m_size{ 0 }
{}

template <typename T>
MyVector::MyVector(const MyVector& other)
	:m_data{ new T[other.m_size] },
	m_size{ other.m_size }
{
	//Change to begin() and end() once u have added Iterator support
	std::copy(other.m_data, other.m_data + other.m_size, m_data);
}

template <typename T>
MyVector::MyVector(MyVector&& other)
	:m_data{ other.m_data },
	m_size{ other.m_size }
{
	other.m_data = nullptr;
	other.m_size = 0
}
