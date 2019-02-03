#pragma once
#include <list>
#include <stdexcept>

/*
Note that Push, Pop and GetMin are all O(1) operations.
1. When pushing into the stack, push into min stack if the pushed value is less than value at head of min stack.
2. When popping from the stack, pop from the min stack if the value popped is equal to value at head of min stack.
*/
template <typename T>
class MyStackConstMin
{
public:
	MyStackConstMin()
		:m_stack{}, m_minstack{}
	{}
	MyStackConstMin(const MyStackConstMin&) = delete;
	MyStackConstMin(MyStackConstMin&&) = delete;
	MyStackConstMin& operator=(const MyStackConstMin&) = delete;
	void pop();
	void push(const T& item);
	T GetMin() const;
	T peek() const
	{
		return m_stack.front();
	}
private:
	std::list<T> m_stack;
	std::list<T> m_minstack;
};

template <typename T>
MyStackConstMin<T>::pop()
{
	if (m_stack.empty())
		throw std::out_of_range{"Stack is empty mate"};

	auto top = peek();
	m_stack.pop_front();

	if (top == m_minstack.front())
		m_minstack.pop_front();

}

template <typename T>
MyStackConstMin<T>::push(const T& item)
{
	m_stack.push_front(item);
	if (m_minstack.front() < item)
		m_minstack.push_front(item);
}

template <typename T>
T MyStackConstMin<T>::GetMin() const
{
	return m_minstack.front();
}