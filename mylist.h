#pragma once

#include <utility>

template <typename T>
class MyList
{
	struct Node
	{
		Node(const T& data)
			:m_data(data),
			m_prev(0),
			m_next(0)
		{}
		~Node()
		{
			std::cout << "Deleting node with value: " << m_data << std::endl;
		};
		T m_data;
		Node* m_prev;
		Node* m_next;
	};
	Node* m_head;
	Node* m_tail;
	size_t m_size;
public:
	MyList();
	MyList(const MyList& rhs) = delete;
	~MyList();
	bool add(const T& item);
	bool add(size_t index, const T& item);
	bool addFirst(const T& item);
	size_t size() const;
	T remove(size_t index);
	T remove(const T& item);
	void reverse();

	//For a doubly-linked list this is fairly trivial
	//Implement this by assuming we are a SIngly-linked list
	void remove(Node* item);
	void print() const;
	void clear();
};

template <typename T>
MyList<T>::MyList()
	:m_head(0),
	m_tail(0),
	m_size(0)
{}

template <typename T>
MyList<T>::~MyList()
{
	for (auto node = m_head; node;)
	{
		auto to_delete = node;
		node = node->m_next;
		delete to_delete;
	}
}

//This adds an element at the end
template <typename T>
bool MyList<T>::add(const T& item)
{
	if (!m_head)
	{
		//This is an empty List
		m_head = new Node(item);
		m_tail = m_head;
	}
	else
	{
		//There is atleast one element in the list
		auto new_item = new Node(item);
		new_item->m_prev = m_tail;
		m_tail->m_next = new_item;
		m_tail = new_item;
	}
	++m_size;
	return true;
}

template <typename T>
bool MyList<T>::add(size_t index, const T& item)
{
	if (index >= m_size)
		return false;
	auto node = m_head;
	for (size_t i = 0; i != index; node = node->m_next, ++i)
	{ }
	node->m_data = item;
	return true;
}

template <typename T>
T MyList<T>::remove(size_t index)
{
	if (index >= m_size)
		return false;
	auto node = m_head;
	for (size_t i = 0; i != index; node = node->m_next, ++i)
	{
	}

	auto item = node->m_data;
	auto prev = node->m_prev;
	auto next = node->m_next;

	if (prev)
	{
		prev->m_next = next;
	}
	else
	{
		//This must be the head we are removing
		//We will need to update the m_head 
		m_head = next;
	}

	if (next)
	{
		next->m_prev = prev;
	}
	else
	{
		//This must be the tail we are removing
		//We will need to update m_tail
		m_tail = prev;
	}
	--m_size;
	delete node;
	return item;
}

template <typename T>
void MyList<T>::remove(Node* item)
{
	//We are assuming this is a singly-linked when its not.
	//The challenge is to delete the node pointed to by item.
	//In a doubly linked list, this is trivial since the node
	//will have pointers to the previous and next nodes. For
	//Singly list list, we only have the next pointer.
	//Note that this doesnt work for the tail node.
	if (!item || !item->m_next)
		return;
	auto next = item->m_next;
	item->m_data = next->m_data;
	item->m_next = next->m_next;
	delete next;
}

template <typename T>
T MyList<T>::remove(const T& item)
{
	Node* match = nullptr;
	for (auto current = m_head; current; current = current->m_next)
	{ 
		if (current->m_data == item)
		{
			match = current;
			break;
		}
	}
	if (!match)
		return T();
	//At this point I have a match

	auto value = match->m_data;
	auto prev = match->m_prev;
	auto next = match->m_next;

	if (prev)
	{
		prev->m_next = next;
	}
	else
	{
		//I must be the head here
		m_head = next;
	}

	if (next)
	{
		next->m_prev = prev;
	}
	else
	{
		m_tail = prev;
	}

	--m_size;
	delete match;
	return value;
}

template <typename T>
bool MyList<T>::addFirst(const T& item)
{
	if (!m_head)
		return add(item);
	auto new_item = new Node(item);
	m_head->m_prev = new_item;
	new_item->m_next = m_head;
	m_head = new_item;
	++m_size;
	return true;
}

template <typename T>
size_t MyList<T>::size() const
{
	return m_size;
}

template <typename T>
void MyList<T>::clear()
{
	for (auto node = m_head; node;)
	{
		auto to_delete = node;
		node = node->m_next;
		delete to_delete;
	}
	m_head = m_tail = 0;
	m_size = 0;
}

//The algorithm for reversing is quite straightforward.
//1. Iterate through each node and swap its next and previous pointers.
//2. swap head and tail pointers.
//3. In some questions u will only have a pointer to head and in which case u have deduce tail at end of loop rather than swapping head and tail
template <typename T>
void MyList<T>::reverse()
{
	auto current = m_head;
	Node* temp = nullptr;
	while (current)
	{
		temp = current;//temp will hold pointer to tail. Just incase u are working with a list which doesnt store its tail.
		std::swap(current->m_next, current->m_prev);
		//The next node is now the previous because of the swap we did above
		current = current->m_prev;
	}
	m_head = temp;
	//std::swap(m_head, m_tail);
}

template <typename T>
void MyList<T>::print() const
{
	for (auto node = m_head; node; node = node->m_next)
	{
		std::cout << node->m_data << std::endl;
	}
}