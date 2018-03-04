#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ProducerConsumer
{
public:
	ProducerConsumer();
	void operator()();
private:
	void Produce();
	void Consume();
	int m_total;
	std::queue<int> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};
