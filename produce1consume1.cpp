#include "produce1consume1.h"
#include <iostream>

namespace T1
{
	std::vector<int> numbers{};
	std::mutex mutex;
	std::condition_variable condition;
	const static int ITEMS = 10;

	void Produce()
	{
		for (int i = 0; i < ITEMS; ++i)
		{
			std::unique_lock<std::mutex> lock{mutex};
			numbers.push_back(i);
			condition.notify_all();
			condition.wait(lock);
		}
	}

	void Consume()
	{
		for (int i = 0; i < ITEMS; ++i)
		{
			std::unique_lock<std::mutex> lock{mutex};
			while(numbers.size() != i + 1)
				condition.wait(lock);
			std::cout << "processed item with value " << numbers.back() << std::endl;
			condition.notify_all();
		}
	}
}