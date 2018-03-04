#pragma once
#include <memory>

template <typename T>
struct Node
{
	Node(const T& rhs)
		:m_data(rhs),
		m_right(0),
		m_left(0)
	{
	};
	~Node()
	{
		std::cout << "Deletimg node with value: " << m_data << std::endl;
	};
	T m_data;
	Node* m_right;
	Node* m_left;
};

template <typename T>
class MyTree
{
public:
	MyTree();
	//MyTree(const MyTree& rhs);
	//MyTree& operator=(const MyTree& rhs);
	//const MyTree& operator=(const MyTree& rhs) const;
	void insert(const T& item);
	Node<T>* find(const T& item);
	const Node<T>* find(const T& item) const;
	void printInOrder();
	~MyTree();
private:
	Node<T>* m_root;
	void doInsert(Node<T>*& current, const T& item);
	Node<T>* doFind(Node<T>* current, const T& item);
	void doPrintInOrder(Node<T>* current);
	void removeSubTree(Node<T>* current);
};

template <typename T>
MyTree<T>::MyTree()
	:m_root(0)
{
}

template <typename T>
MyTree<T>::~MyTree()
{
	removeSubTree(m_root);
}

template <typename T>
void MyTree<T>::insert(const T& item)
{
	doInsert(m_root, item);
}

template <typename T>
void MyTree<T>::doInsert(Node<T>*& current, const T& item)
{
	if (current)
	{
		if (item < current->m_data)
		{
			doInsert(current->m_left, item);
		}
		else
		{
			doInsert(current->m_right, item);
		}
	}
	else
	{
		current = new Node<T>(item);
		std::cout << "Created a new Node with address = " << current << " and value = " << current->m_data << std::endl;
	}
}

template <typename T>
Node<T>* MyTree<T>::find(const T& item)
{
	return doFind(m_root, item);
}

template <typename T>
const Node<T>* MyTree<T>::find(const T& item) const
{
	return doFind(m_root, item);
}

template <typename T>
Node<T>* MyTree<T>::doFind(Node<T>* current, const T& item)
{
	if (current)
	{
		if (item == current->m_data)
		{
			return current;
		}
		else if (item < current->m_data)
		{
			return doFind(current->m_left, item);
		}
		else
		{
			return doFind(current->m_right, item);
		}
	}
	else
	{
		return 0;
	}
}

template <typename T>
void MyTree<T>::printInOrder()
{
	doPrintInOrder(m_root);
}

template <typename T>
void MyTree<T>::doPrintInOrder(Node<T>* current)
{
	if (current)
	{
		if (current->m_left)
		{
			doPrintInOrder(current->m_left);
		}
		std::cout << "Item : " << current->m_data << std::endl;
		if (current->m_right)
		{
			doPrintInOrder(current->m_right);
		}
	}
	else
	{
		std::cout << "Node is empty" << std::endl;
	}
}

template <typename T>
void MyTree<T>::removeSubTree(Node<T>* current)
{
	if (current)
	{
		if (current->m_left)
		{
			removeSubTree(current->m_left);
		}
		if (current->m_right)
		{
			removeSubTree(current->m_right);
		}
		delete current;
	}
}