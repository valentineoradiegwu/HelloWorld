#pragma once
#include <atomic>
#include <thread>
#include <future>
#include "ThreadSafeQueue.h"

//TaskType is the function signature
//T() for the time being. We use boost bind to supply all the arguments to the packaged_task when we enqueue.

template <typename TaskType>
class ThreadPool
{
public:
	ThreadPool();
	ThreadPool(size_t threads);
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	void push(std::packaged_task<TaskType> job);
	~ThreadPool();
private:
	ThreadSafeQueue<std::packaged_task<TaskType>> m_queue;
	std::vector<std::thread> m_threads;
	std::atomic<bool> m_shutdown;
	void execute_task();
	void launch_threads(int threads);
	static int GetHardwareThreads();
};

template <typename TaskType>
int ThreadPool<TaskType>::GetHardwareThreads()
{
	int hardware_threads = std::thread::hardware_concurrency();
	return hardware_threads ? hardware_threads : 2;
}

template <typename TaskType>
void ThreadPool<TaskType>::launch_threads(int threads)
{
	m_threads.reserve(threads);
	for (int i = 0; i < threads; ++i)
		m_threads.push_back(std::thread{ &ThreadPool<TaskType>::execute_task, this });
}

template <typename TaskType>
ThreadPool<TaskType>::ThreadPool()
	:m_queue{},
	m_threads{},
	m_shutdown{ false }
{
	auto hardware_threads = ThreadPool<TaskType>::GetHardwareThreads();
	launch_threads(hardware_threads);
}

template <typename TaskType>
ThreadPool<TaskType>::ThreadPool(size_t threads)
	:m_queue{},
	m_threads{},
	m_shutdown{ false }
{
	auto hardware_threads = std::min(ThreadPool<TaskType>::GetHardwareThreads(), threads);
	launch_threads(hardware_threads);
}

template <typename TaskType>
void ThreadPool<TaskType>::push(std::packaged_task<TaskType> job)
{
	m_queue.push(job);
}

template <typename TaskType>
void ThreadPool<TaskType>::execute_task()
{
	while (!m_shutdown)
	{
		std::packaged_task<TaskType> job;
		m_queue.pop(job);
		job();
	}
}

template <typename TaskType>
ThreadPool<TaskType>::~ThreadPool()
{
	m_shutdown = true;
	for (auto& thread : m_threads)
		thread.join();
}