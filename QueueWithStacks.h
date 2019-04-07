#pragma once
#include <stack>

template <typename T>
class MyQueue
{
	std::stack<T> inbox;
	std::stack<T> outbox;
public:
	MyQueue() = default;
	void Enqueue(const T& item);
	void Dequeue();
	void Print();
};

template <typename T>
void MyQueue<T>::Enqueue(const T& item)
{
	inbox.push(item);
}

template <typename T>
void MyQueue<T>::Dequeue()
{
	if (outbox.empty())
	{
		while (!inbox.empty())
		{
			outbox.push(inbox.top());
			inbox.pop();
		}
	}
	outbox.pop();
}

template <typename T>
void MyQueue<T>::Print()
{
	if (outbox.empty())
	{
		while (!inbox.empty())
		{
			outbox.push(inbox.top());
			inbox.pop();
		}
	}
	std::cout << outbox.top() << std::endl;
}
