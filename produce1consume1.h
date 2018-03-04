#pragma once
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>

namespace T1
{ 
	void Produce();
	void Consume();
}

namespace T2
{

	template<typename Iter>
	struct AccumulateBlock
	{
		void operator()(Iter begin, Iter end, typename std::iterator_traits<Iter>::value_type& total)
		{
			std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;
			typename std::iterator_traits<Iter>::value_type result = 0;
			for (; begin != end; ++begin)
				result = result + *begin;
			total = result;
		}
	};

	template<typename Iter>
	typename std::iterator_traits<Iter>::value_type Accumulate(Iter& begin, Iter& end, typename std::iterator_traits<Iter>::value_type init)
	{
		using value_type = std::iterator_traits<Iter>::value_type;
		auto size = std::distance(begin, end);
		if (!size)
			return init;

		int number_of_threads = std::thread::hardware_concurrency();
		
		int min_block = 10;
		int min_number_of_threads = size % min_block == 0 ? size / min_block : (size / min_block) + 1;
		int threads = std::min(min_number_of_threads, number_of_threads);
		int block_size = (threads == number_of_threads)? size / threads : min_block;

		std::vector<std::thread> jobs(threads - 1);
		std::vector<value_type> results(threads);
		Iter next = begin;
		for (int i = 0; i < (threads - 1); ++i)
		{
			next = next + block_size;
			jobs[i] = std::thread{ AccumulateBlock<Iter>(), begin, next, std::ref(results[i]) };
			begin = next;
		}
		AccumulateBlock<Iter>()(begin, end, std::ref(results[threads - 1]));

		for (auto& thread : jobs)
			thread.join();

		return std::accumulate(results.begin(), results.end(), init);
	}
}