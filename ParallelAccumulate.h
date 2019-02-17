#pragma once
#include <thread>
#include <functional>

template <typename Iter, typename CONT>
void doAccumulate(Iter begin, Iter end, CONT& results, int idx)
{
	std::cout << "Running Thread " << idx << std::endl;
	auto sum = std::accumulate(begin, end, 0);
	results[idx] = sum;
}

template <typename CONT>
typename CONT::value_type ParallelAccumulate(const CONT& input, typename CONT::value_type init)
{
	const auto size = input.size();
	const int min_block = 25;
	const int hardware_threads = std::thread::hardware_concurrency();
	std::cout << "Number of hardware threads available is " << hardware_threads << std::endl;
	//This basically calculated the ceiling of the division.
	//Say we have 1000 items with a min block of 25 we will have max of 40.
	//If we had 1001 with same min block we want to compute 41. 
	const int max_threads = size % min_block == 0 ? size /min_block: (size / min_block) + 1;

	//If hardware threads is 0, we dont even do context switching and let a single thread deal with computation
	auto threads = std::min(hardware_threads ? hardware_threads : 0, max_threads);
	std::cout << "Number of worker threads calculated " << threads << std::endl;
	auto actual_block_size = size / threads;
	std::vector<std::thread> jobs;
	auto begin = input.begin();
	auto end = begin;
	std::vector<decltype(init)> results(threads - 1);

	for (auto i = 0; i < threads - 1; ++i)
	{
		std::advance(end, actual_block_size);
		jobs.push_back(std::thread{ doAccumulate<decltype(begin), decltype(results)>, begin, end, std::ref(results), i });
		begin = end;
	}

	for (auto& job : jobs)
		job.join();

	auto sum = std::accumulate(begin, input.end(), init);

	if (!results.empty())
		sum += std::accumulate(results.begin(), results.end(), 0);

	return sum;
}


