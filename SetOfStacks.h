#pragma once
#include <vector>
#include <list>
#include <stdexcept>

template <typename T>
class SetOfStacks
{
public:
	SetOfStacks(int maxStack = 10);
	void push_front(const T& item);
	T pop_front();
	T peek() const;
	size_t size() const;
private:
	std::vector<std::list<T>> m_stacks;
	int m_maxStackSize;
};

template <typename T>
SetOfStacks<T>::SetOfStacks(int maxStack)
	:m_stacks{},
	m_maxStackSize{maxStack}
{
	if (maxStack < 1)
		throw std::invalid_argument{ "The size of each stack must be greater than 1" };
}

template <typename T>
void SetOfStacks<T>::push_front(const T& item)
{
	if (m_stacks.empty())
		m_stacks.push_back(std::list<T>{});

	std::stack<T>& front = m_stacks.back();
	if (front.size() < 10)
	{
		front.push_front(item);
	}
	else
	{
		m_stacks.push_back(std::list<T>{});
		m_stacks.back().push_front(item);
	}
}

template <typename T>
T SetOfStacks<T>::pop_front()
{
	if (m_stacks.empty())
		throw std::invalid_argument{ "The stack is empty" };

	std::stack<T>& front = m_stacks.back();
	front.pop_front();

	if (front.empty())
		m_stacks.pop_back();
}

template <typename T>
T SetOfStacks<T>::peek() const
{
	if (m_stacks.empty())
		throw std::invalid_argument{ "The stack is empty" };
	const std::stack<T>& front = m_stacks.back();
	return *(front.begin());
}

template <typename T>
size_t SetOfStacks<T>::size() const
{
	auto size = m_stacks.size();
	if (size)
	{
		size = ((size -1) * 10) + m_stacks.back().size()
	}
	return size;
}
