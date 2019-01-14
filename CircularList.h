#pragma once
#include <cassert>
/*
There appears to be a few ways to implement a circular linkedlist.
Here I maintain the tail of the list and move the tail if i add or
remove at the end. the implied head of the tail is tail->m_next.
1. Add at Back is O(1)
2. Add at front is O(1)
3. Remove front is O(1)
4. Remove back is O(N) this is because we need to have a pointer to the one b4 back and we have to iterate from the logical head.
*/

template <typename T>
class CircularList
{
	template <typename T>
	struct Node
	{
		Node(const T& item)
			:m_data{ item },
			m_next{nullptr}
		{};
		T m_data;
		Node* m_next;
	};
	Node* m_tail;
public:
	CircularList();
	T pop_front();
	T pop_back();
	void push_front(const T& item);
	void push_back(const T& item);
	bool find(const T& item);
	void delete_node(const T& item);
	//~CircularList();
};

template <typename T>
CircularList<T>::CircularList()
	:m_tail{nullptr}
{}

template <typename T>
T CircularList<T>::pop_front()
{
	assert(m_tail);
	auto head = m_tail->m_next;
	if (head != m_tail)
	{
		auto new_head = head->m_next;
		m_tail->m_next = new_head;
	}
	auto result = head->m_data;
	delete head;
	return result;
}

template <typename T>
T CircularList<T>::pop_back()
{
	assert(m_tail);
	Node* tail = m_tail;
	auto begin = m_tail->m_next;
	if (begin == m_tail)
	{
		m_tail = nullptr;
	}
	else
	{
		while (begin->m_next != m_tail)
		{
			begin = begin->m_next;
		}
		begin->m_next = m_tail->m_next;
		m_tail = begin;
	}
	auto result = tail->m_data;
	delete tail;
	return result;

	if (head != m_tail)
	{
		auto new_head = head->m_next;
		m_tail->m_next = new_head;
	}
	auto result = head->m_data;
	delete head;
	return result;
}

template <typename T>
void CircularList<T>::push_front(const T& item)
{
	Node<T>* node = new Node{ item };
	if (!m_tail)
	{
		m_tail = node;
		m_tail->m_next = m_tail;
	}
	else
	{
		node->m_next = m_tail->m_next;
		m_tail->m_next = node;
	}
}

template <typename T>
void CircularList<T>::push_back(const T& item)
{
	Node<T>* node = new Node{ item };
	if (!m_tail)
	{
		m_tail = node;
		m_tail->m_next = m_tail;
	}
	else
	{
		m_tail->m_next = node;
		node->m_next = m_tail->m_next;
		m_tail = node;
	}
}

template <typename T>
bool CircularList<T>::find(const T& item)
{
	if (!m_tail)
		return false;

	auto current = m_tail;

	do
	{
		if (current->m_data == item)
			return true;
		current = current->m_next;
	} while (current != m_tail);

	return false;
}

template <typename T>
void CircularList<T>::delete_node(const T& item)
{
	assert(m_tail);
	auto current = m_tail->m_next;
	Node* prev = m_tail;

	// The circular buffer only has one element.
	if (prev == current)
	{
		delete current;
		m_tail = nullptr;
	}

	do
	{
		if (current->m_data == item)
		{
			prev->m_next = current->m_next;
			if (current == m_tail)
				m_tail = prev;
			delete current;
			return;
		}
		prev = current;
		current = current->m_next;
	} while (current != m_tail->m_next);
}

