#pragma once
#include <mutex>
#include <stack>
#include <exception>
#include <memory>

/*
1. Pop in a list doesnt return the value being popped. Copying out the value could hit an out of memory exception which implies that we've lost the value popped.
2. The conventional solution is to call top() and then pop().
3. While this solves the exception safety issue, it exposes us to multithreading issues.
4. top() and pop() should be atomic and if not then a thread can be interleaved in between and cause race conditions.
5. The issue is solved by having pop() create a shared_ptr of the data returned by top since copying the shared_ptr is unlikely to throw since its just a 2 pointer copy.
*/

template <typename T>
class ThreadSafeList
{
	mutable std::mutex m_lock;
	std::stack<T> m_stack;
public:
	ThreadSafeList()
		:m_lock{},
		m_stack{}
	{}
	ThreadSafeList(const ThreadSafeList& other)
		:m_lock{}
	{
		std::lock_guard<std::mutex>{m_lock};
		m_stack = other.m_stack;
	}
	ThreadSafeList& operator=(const ThreadSafeList& other)
	{
		if (this != &other)
		{
			std::unique_lock<std::mutex> lhs{ m_lock, std::defer_lock };
			std::unique_lock<std::mutex> rhs{ other.m_lock, std::defer_lock };
			std::lock(lhs, rhs);
			m_stack = other.m_stack;
		}
		return *this;
	}
	std::unique_ptr<T> pop()
	{
		std::lock_guard<std::mutex>{m_lock};
		if (m_stack.empty())
			throw std::logic_error{ "List is empty" };
		std::unique_ptr<T> item{ std::make_unique<T>{m_stack.top()} };
		m_stack.pop();
		return item;
	}
	void push(const T& item)
	{
		std::lock_guard<std::mutex>{m_lock};
		m_stack.push(item);
	}
	bool empty() const
	{
		std::lock_guard<std::mutex>{m_lock};
		return m_stack.empty();
	}
	bool size() const
	{
		std::lock_guard<std::mutex>{m_lock};
		return m_stack.size();
	}
};
