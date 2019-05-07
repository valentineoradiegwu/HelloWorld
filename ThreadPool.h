#pragma once
#include <atomic>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>

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
	void push(std::packaged_task<TaskType>& job);
	bool pop(std::packaged_task<TaskType>& job);
	void shutdown();
	~ThreadPool();
private:
	std::queue<std::packaged_task<TaskType>> m_queue;
	std::condition_variable m_cond;
	std::mutex m_mutex;
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
	{
		auto thread = std::thread{ &ThreadPool<TaskType>::execute_task, this };
		std::cout << "Launching Thread " << thread.get_id() << std::endl;
		m_threads.push_back(std::move(thread));
	}
}

template <typename TaskType>
void ThreadPool<TaskType>::shutdown()
{
	if (!m_shutdown)
	{
		m_shutdown = true;
		m_cond.notify_all();
	}
}

template <typename TaskType>
ThreadPool<TaskType>::ThreadPool()
	:m_queue{},
	m_cond{},
	m_mutex{},
	m_threads{},
	m_shutdown{ false }
{
	launch_threads(ThreadPool<TaskType>::GetHardwareThreads());
}

template <typename TaskType>
ThreadPool<TaskType>::ThreadPool(size_t threads)
	:m_queue{},
	m_cond{},
	m_mutex{},
	m_threads{},
	m_shutdown{ false }
{
	launch_threads(std::min(ThreadPool<TaskType>::GetHardwareThreads(), threads));
}

template <typename TaskType>
void ThreadPool<TaskType>::push(std::packaged_task<TaskType>& job)
{
	{
		std::lock_guard<std::mutex> lock{ m_mutex };
		m_queue.push(std::move(job));
	}
	m_cond.notify_one();
}

template <typename TaskType>
bool ThreadPool<TaskType>::pop(std::packaged_task<TaskType>& job)
{
	std::unique_lock<std::mutex> lock{ m_mutex };
	m_cond.wait(lock, [this] {return this->m_shutdown || !this->m_queue.empty(); });
	if (m_queue.empty())
		return true;

	job = std::move(m_queue.front());
	m_queue.pop();
	return false;
}

template <typename TaskType>
void ThreadPool<TaskType>::execute_task()
{
	while (true)
	{
		std::packaged_task<TaskType> job;
		auto shutdown = pop(job);
		if (shutdown)
		{
			std::cout << "Shutting Down Thread " << std::this_thread::get_id() << std::endl;
			return;
		}
		job();
	}
}

template <typename TaskType>
ThreadPool<TaskType>::~ThreadPool()
{
	shutdown();
	for (auto& thread : m_threads)
		thread.join();
}