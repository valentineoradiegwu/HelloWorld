#pragma once
#include <deque>
/*
1. Any object can be used in the enhanced for loop if it defines a begin and end and the objects returned by those support ++
2. The default keyword is used when a default operator is not automatically generated or we would like to redeclare it with a new access modifier
   a. a user defined operator exist which suppresses default
   b. rules preclude the compiler from generating
3. We made a CustomStack<int> assignable to a CustomStack<double> by using a member function template(line 26) in addition to a class template
4. A const object can only invoke member functions marked const. A non-const object however can call both const and non-const members.
5. A list of initializers during construction is supported by creating a ctor that takes a std::initializer_list
6. A template constructor does not hide the implicitly generated copy constructor.

*/
template <typename T, typename CONT = std::deque<T> >
class CustomStack
{
	CONT m_buffer;
public:
	CustomStack();
	CustomStack(const CustomStack<T, CONT>& rhs);
	CustomStack(CustomStack<T, CONT>&& rhs);
	CustomStack(const std::initializer_list<T>& list);
	T top() const { return m_buffer.front(); };
	typename CONT::size_type size() const { return m_buffer.size(); };
	void pop() { m_buffer.pop_back(); }
	void push(const T& item) { m_buffer.push_back(item); }
	bool empty() const { return m_buffer.empty(); }

	template <typename T2, typename CONT2>
	CustomStack<T, CONT>& operator=(const CustomStack<T2, CONT2>& rhs);
	CustomStack<T, CONT>& operator=(CustomStack<T, CONT>&& rhs);
	CustomStack<T, CONT>& operator=(const CustomStack<T, CONT>& rhs) =default;
	typename CONT::const_iterator begin() const { return m_buffer.cbegin(); }
	typename CONT::const_iterator end() const { return m_buffer.cend(); }
	typename CONT::iterator begin() { return m_buffer.begin(); }
	typename CONT::iterator end() { return m_buffer.end(); }
};

template <typename T, typename CONT>
CustomStack<T, CONT>::CustomStack()
	:m_buffer{}
{}

template <typename T, typename CONT>
CustomStack<T, CONT>::CustomStack(const CustomStack<T, CONT>& rhs)
	:m_buffer{rhs.m_buffer}
{}

template <typename T, typename CONT>
CustomStack<T, CONT>::CustomStack(CustomStack<T, CONT>&& rhs)
	: m_buffer{ std::move(rhs.m_buffer) }
{}

template <typename T, typename CONT>
CustomStack<T, CONT>::CustomStack(const std::initializer_list<T>& list)
	: m_buffer{ list }
{}

template <typename T, typename CONT>
template <typename T2, typename CONT2>
CustomStack<T, CONT>& CustomStack<T, CONT>::operator=(const CustomStack<T2, CONT2>& rhs)
{
	m_buffer.clear();
	for (const auto& i : rhs)
		m_buffer.push_back(i);
	return *this;
}

template <typename T, typename CONT>
CustomStack<T, CONT>& CustomStack<T, CONT>::operator=(CustomStack<T, CONT>&& rhs)
{
	m_buffer = std::move(rhs.m_buffer);
	return *this;
}