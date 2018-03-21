#pragma once
#ifndef MY_STACK_H
#define MY_STACK_H

#include <vector>
#include <deque>
#include <stdexcept>
#include <typeinfo>
#include <iterator>
#include <thread>
#include <future>

template <typename T, typename CONT = std::deque<T> >
class MyStack
{
private:
	CONT m_buffer;

public:
	bool empty() const;
	void push(const T& item);
	T top() const;
	void pop();
	template <typename T2>
	MyStack<T, CONT>& operator=(MyStack<T2, CONT> lhs);
};

template <typename T, typename CONT>
template <typename T2>
MyStack<T, CONT>& MyStack<T, CONT>::operator=(MyStack<T2, CONT> lhs)
{
	m_buffer.clear();
	while (!lhs.empty())
	{
		m_buffer.push_front(lhs.top());
		lhs.pop();
	}
	return *this;
}

template <typename T, typename CONT>
bool MyStack<T, CONT>::empty() const
{
	return m_buffer.empty();
}

template <typename T, typename CONT>
void MyStack<T, CONT>::push(const T& item)
{
	m_buffer.push_back(item);
}

template <typename T, typename CONT>
void MyStack<T, CONT>::pop()
{
	if (m_buffer.empty())
		throw std::out_of_range("Empty stack");
	m_buffer.pop_back();
}

template <typename T, typename CONT>
T MyStack<T, CONT>::top() const
{
	if (m_buffer.empty())
		throw std::out_of_range("Empty stack");
	return m_buffer.back();
}

template <typename T, int MAXSIZE = 5>
class MyStack2
{
private:
	T m_buffer[MAXSIZE];
	int m_stack_ptr;
public:
	MyStack2();
	bool empty() const;
	T top() const;
	void pop();
	void push(const T& item);
	int size() const;
	int capacity() const;
};

template <typename T, int MAXSIZE>
MyStack2<T, MAXSIZE>::MyStack2()
	:m_stack_ptr(-1)
{
}

template <typename T, int MAXSIZE>
bool MyStack2<T, MAXSIZE>::empty() const
{
	return m_stack_ptr == -1;
}

template <typename T, int MAXSIZE>
T MyStack2<T, MAXSIZE>::top() const
{
	if (empty())
		throw std::out_of_range("Empty stack");
	return m_buffer[m_stack_ptr];
}

template <typename T, int MAXSIZE>
void MyStack2<T, MAXSIZE>::pop()
{
	if (empty())
		throw std::out_of_range("Empty stack");
	--m_stack_ptr;
}

template <typename T, int MAXSIZE>
void MyStack2<T, MAXSIZE>::push(const T& item)
{
	if (m_stack_ptr == MAXSIZE - 1)
		throw std::out_of_range("Full stack");
	m_buffer[++m_stack_ptr] = item;;
}

template <typename T, int MAXSIZE>
int MyStack2<T, MAXSIZE>::size() const
{
	return m_stack_ptr + 1;
}

template <typename T, int MAXSIZE>
int MyStack2<T, MAXSIZE>::capacity() const
{
	return MAXSIZE;
}

template <typename T>
class Val
{
private:
	T m_member;

public:
	Val(const T& val);
	std::string getType() const;
};

template <typename T>
Val<T>::Val(const T& val)
	:m_member(val)
{
}

template <typename T>
std::string Val<T>::getType() const
{
	const std::type_info& ti = typeid(m_member);
	return ti.name();
}

template <>
class Val<std::string>
{
private:
	std::string m_member;

public:
	Val(const std::string& val);
	std::string getType() const;
};

Val<std::string>::Val(const std::string& val)
	:m_member(val)
{
}

std::string Val<std::string>::getType() const
{
	const std::type_info& ti = typeid(m_member);
	return ti.name();
	//return "std::string baby";
}

template <typename T>
class Val<T*>
{
private:
	T* m_member;

public:
	Val(T* val);
	std::string getType() const;
};

template <typename T>
Val<T*>::Val(T* val)
	:m_member(val)
{
}

template <typename T>
std::string Val<T*>::getType() const
{
	const std::type_info& ti = typeid(m_member);
	return ti.name();
}

// Having a go at the templated typedefs from C++ 11
template <typename CONT>
using iterator_category = typename std::iterator_traits<typename CONT::const_iterator>::iterator_category;

template <typename CONT>
using value_type = typename CONT::value_type;

template <typename Iter>
typename std::iterator_traits<Iter>::value_type doAccumulate(Iter start, Iter end)
{
	return std::accumulate(start, end, 0);
}

template <typename CONT>
typename value_type<CONT> ParrallelAccumulatorImpl(const CONT& randomAccessSequence, size_t numThreads, std::random_access_iterator_tag)
{
	using value_type = value_type<CONT>;
	using const_iterator = typename CONT::const_iterator;
	using TaskType = value_type(const_iterator, const_iterator);

	std::packaged_task<TaskType> task1 {doAccumulate<const_iterator>};
	std::packaged_task<TaskType> task2 {doAccumulate<const_iterator>};

	std::future<value_type> f1{task1.get_future()};
	std::future<value_type> f2{task2.get_future()};

	std::thread t1{std::move(task1), randomAccessSequence.begin(), randomAccessSequence.begin() + randomAccessSequence.size() / 2};
	std::thread t2{std::move(task2), randomAccessSequence.begin() + randomAccessSequence.size() / 2, randomAccessSequence.begin() + randomAccessSequence.size()};

	t1.join();
	t2.join();

	return f1.get() + f2.get();
}

template <typename CONT, size_t NUM_OF_THREADS = 2>
typename CONT::value_type ParrallelAccumulator(const CONT& randomAccessSequence)
{
    return ParrallelAccumulatorImpl(randomAccessSequence, 
	                                NUM_OF_THREADS, 
	                                iterator_category<CONT>{});
}

#endif
