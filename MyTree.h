#pragma once
#include <memory>
#include <vector>
#include <list>

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
	T findMin() const;
	T findMax() const;
	~MyTree();
	void GetNodesPerLevel() const;
	//static friend int GetKthLargestNode(Node<T>* tree, int K);
private:
	Node<T>* m_root;
	void doInsert(Node<T>*& current, const T& item);
	Node<T>* doFind(Node<T>* current, const T& item);
	void doPrintInOrder(Node<T>* current);
	void removeSubTree(Node<T>* current);
	T doFindMin(Node<T>* current) const;
	T doFindMax(Node<T>* current) const;
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
	if (m_root)
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

template <typename T>
T MyTree<T>::doFindMin(Node<T>* current) const
{
	if (current->m_left)
		return doFindMin(current->m_left);

	return current->m_data;
}
template <typename T>
T MyTree<T>::doFindMax(Node<T>* current) const
{
	if (current->m_right)
		return doFindMax(current->m_right);

	return current->m_data;
}

template <typename T>
T MyTree<T>::findMin() const
{
	return doFindMin(m_root);
}

template <typename T>
T MyTree<T>::findMax() const
{
	return doFindMax(m_root);
}

template <typename T>
void MyTree<T>::GetNodesPerLevel() const
{
	if (m_root)
	{
		std::list<Node<T>*> eachLevel{};
		eachLevel.push_back(m_root);
		std::cout << "This level has " << m_root->m_data << std::endl;
		std::vector<std::list<Node<T>*>> levels{};
		levels.push_back(eachLevel);
		while (true)
		{
			auto& prevLevel = levels.back();
			eachLevel.clear();
			std::cout << "This level has ";
			for (auto node : prevLevel)
			{
				if (node->m_left)
				{
					std::cout << node->m_left->m_data << " ";
					eachLevel.push_back(node->m_left);
				}
				if (node->m_right)
				{
					std::cout << node->m_right->m_data << " ";
					eachLevel.push_back(node->m_right);
				}
			}
			std::cout << std::endl;
			if (eachLevel.empty())
				break;
			else
				levels.push_back(eachLevel);
		}
	}
}