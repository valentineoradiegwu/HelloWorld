#pragma once
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
public:
	ThreadSafeQueue();
	ThreadSafeQueue(const ThreadSafeQueue&) = delete;
	ThreadSafeQueue(ThreadSafeQueue&&) = delete;
	void push(const T& item);
	void push(T&& item);
	// Pop is a blocking pop. It waits for queue to have data.
	void pop(T&);
	std::unique_ptr<T> pop();
	bool try_pop(T&);
	std::unique_ptr<T> try_pop();
	bool empty() const 
	{ 
		std::lock_guard<std::mutex> lock{ m_mutex };
		return m_queue.empty(); 
	}
	typename std::queue<T>::size_type size() const
	{ 
		return m_queue.size(); 
	}
};

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
	:m_queue{}
{}

template <typename T>
void ThreadSafeQueue<T>::push(const T& item)
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	m_queue.push(item);
	m_cond.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::push(T&& item)
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	//I can probably get away with using std::move here
	m_queue.push(std::forward<T>(item));
	m_cond.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::pop(T& item)
{
	std::unique_lock<std::mutex> lock{ m_mutex };
	m_cond.wait(lock, [this] {return !this->m_queue.empty(); });
	item = m_queue.front();
	m_queue.pop();
}

template <typename T>
std::unique_ptr<T> ThreadSafeQueue<T>::pop()
{
	std::unique_lock<std::mutex> lock{ m_mutex };
	m_cond.wait(lock, [this] {return !this->m_queue.empty(); });
	std::unique_ptr<T> item = std::make_unique<T>(m_queue.front());
	m_queue.pop();
	return item;
}

template <typename T>
bool ThreadSafeQueue<T>::try_pop(T& item)
{
	std::lock_guard<std::mutex> lock{ m_mutex, std::defer_lock };
	auto has_lock = std::try_lock(lock);
	if (!has_lock || m_queue.empty())
		return has_lock;
	item = m_queue.front();
	m_queue.pop();
	return true;
}

template <typename T>
std::unique_ptr<T> ThreadSafeQueue<T>::try_pop()
{
	std::lock_guard<std::mutex> lock{ m_mutex, std::defer_lock };
	auto has_lock = std::try_lock(lock);
	std::unique_ptr<T> item{};
	if (!has_lock || m_queue.empty())
		return item;
	item = std::make_shared<T>(m_queue.front());
	m_queue.pop();
	return item;
}