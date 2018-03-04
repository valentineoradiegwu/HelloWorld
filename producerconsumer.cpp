#include "producerconsumer.h"
#include <iostream>

ProducerConsumer::ProducerConsumer()
	:m_total(10000),
	m_queue(),
	m_mutex(),
	m_condition()
{

}

void ProducerConsumer::Produce()
{
	int produced = 0;
	while (produced < m_total)
	{
		std::lock_guard<std::mutex> lck(m_mutex);
		while (true)
		{
			m_queue.push(++produced);
			std::cout << "Produced an item from queue with value = " << produced << std::endl;
			if (produced % 10 == 0)
			{
				m_condition.notify_all();
				break;
			}
		}
	}
}

void ProducerConsumer::Consume()
{
	int consumed = 0;
	while (consumed < m_total)
	{
		std::unique_lock<std::mutex> lck(m_mutex);
		while (m_queue.empty())
		{
			m_condition.wait(lck);
		}

		while (!m_queue.empty())
		{
			std::cout << "Consumed an item from queue with value = " << m_queue.front() << std::endl;
			m_queue.pop();
			++consumed;
		}
	}
}

void ProducerConsumer::operator()()
{
	std::thread consume(&ProducerConsumer::Consume, this);
	std::thread produce(&ProducerConsumer::Produce, this);
	consume.join();
	produce.join();
}