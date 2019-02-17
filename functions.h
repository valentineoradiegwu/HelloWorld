#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>      // std::invalid_argument
#include <iterator>

std::vector<int> LeetTwoSum(const std::vector<int>& numbers, int target);
std::vector<int> LeetTwoSum2(const std::vector<int>& numbers, int target);
std::vector<int> LeetTwoSumSorted(const std::vector<int>& numbers, int target);
int LeetReverseInt(int input);
int LeetAtoi(const std::string& input);
bool LeetIsPalindrome(int x);
int LeetLongestSubstring(const std::string& s);
std::vector<std::vector<int> > LeetThreeSum(std::vector<int>& nums);
std::vector<std::vector<int> > LeetThreeSum2(std::vector<int>& nums);
int LeetsubarraySum(std::vector<int>& nums, int k);
int LeetMaximumSubarraySum(std::vector<int>& nums, int k);
void PrintDistinctNumbersWithPairs(std::vector<int>& nums);
void PrintDistinctNumbersWithPairs1(std::vector<int>& nums);
void reverseFunc(char* input);
int Factorial(int i);
bool unique_chars(const char* input);
bool unique_chars2(const char* input);
void remove_dupes(char* input);
void remove_dupes2(char* input);
void remove_dupes3(char* input);
std::string MergeStrings(const std::vector<std::string>& iInput);
void setZeros(int matrix[][4]);
int myStrCmp(const char* input1, const char* input2);
bool are_anagrams(const char* input1, const char* input2);
std::string replaceSpaceWithEncoding(char* input);
bool is_substr(const char* input1, const char* input2);
int UtopianTree(int cycles);
int myAtoi(std::string str);
int fib(int n);
template <typename T>
void dbg(const std::string& annotation, const T& item)
{
	std::cout << annotation << ": " << item << std::endl;
}

template <typename CONT>
void printAll(const CONT& container)
{
	for (typename CONT::const_iterator i = container.begin(); i != container.end(); ++i)
	{
		dbg("item", *i);
	}
}

template <typename T>
std::string getType(const T&);

template <typename T>
T max(const std::vector<T>& input)
{
	if input.empty()
		throw std::invalid_argument{ "The input must have at least one value" };
	T max = input[0];
	T secondmax = input[0];
	for (int i = 1; i < input.size(); ++i)
	{
		if (input[i] > max)
		{
			secondmax = max;
			max = input[i];
		}
		else if (input[i] > secondmax)
		{
			secondmax = input[i];
		}
	}
	return secondmax;
}

template <typename T>
std::pair<size_t, size_t> LargestIncreasingSubSequence(const std::vector<T>& input)
{
	size_t lower_bound = 0;
	size_t upper_bound = 0;
	size_t current_lower_bound = 0;
	size_t current_upper_bound = 0;

	for (size_t i = 1; i < input.size(); ++i)
	{
		if (input[i] > input[i - 1])
		{
			current_upper_bound = i;
		}
		else
		{
			if ((current_upper_bound - current_lower_bound) >= (upper_bound - lower_bound))
			{
				upper_bound = current_upper_bound;
				lower_bound = current_lower_bound;
				current_upper_bound = current_lower_bound = i;
			}
		}
	}
	return std::make_pair(lower_bound, upper_bound);
}


template <typename Iter>
bool bin_search(Iter begin, Iter end, const typename std::iterator_traits<Iter>::value_type& key)
{
	while (begin < end)
	{
		auto middle = begin + std::distance(begin, end) / 2;
		if (*middle == key)
			return true;
		else if (*middle > key)
			end = middle;
		else
			begin = middle + 1;
	}
	return false;
}

template <typename Iter>
bool bin_search_recurse(Iter begin, Iter end, const typename std::iterator_traits<Iter>::value_type& key)
{
	if (begin >= end)
		return false;

	auto middle = begin + std::distance(begin, end) / 2;
	if (*middle == key)
		return true;
	else if (*middle > key)
		return bin_search_recurse(begin, middle, key);
	else
		return bin_search_recurse(middle + 1, end, key);
}

// Runtime O(n^2)
// Inplace
// Stable
template <typename Iter>
void SelectionSort(Iter begin, Iter end)
{
	while (begin != end)
	{
		auto min = begin;
		auto next = begin + 1;
		while (next != end)
		{
			if (*next < *min)
				min = next;
			++next;
		}
		auto temp = *begin;
		*begin = *min;
		*min = temp;
		++begin;
	}
}

// Runtime O(n^2)
// Linear in best case which is if th input is already sorted
// Inplace
// Stable
// For a sorted array, we can break down algo to linear by adding a flag.
// If no swaps occur after first pass then the array must be already sorted.
// https://www.youtube.com/watch?v=Jdtq5uKz-w4&list=PL2_aWCzGMAwKedT2KfDMB9YA5DgASZb3U&index=3
template <typename Iter>
void BubbleSort(Iter begin, Iter end)
{
	while (begin != end)
	{
		auto current = begin;
		auto next = current + 1;
		auto is_original_sorted = true;
		while (next != end)
		{
			if (*current > *next)
			{
				auto temp = *current;
				*current = *next;
				*next = temp;
				is_original_sorted = false;
			}
			++current;
			++next;
		}
		if (is_original_sorted) break;
		--end;
	}
}

// Runtime O(n^2) in worst case
// Linear in best case which is if th input is already sorted
// Inplace
// Stable
template <typename Iter>
void InsertionSort(Iter begin, Iter end)
{
	Iter start = begin;
	while (start != end)
	{
		auto current = start;
		auto prev = current - 1;
		while (prev >= begin && *current < *prev)
		{
			std::swap(*current, *prev);
			--current;
			--prev;
		}
		++start;
	}
}

template<typename Iter>
Iter Partition(Iter first, Iter last)
{
	auto pivot = last - 1;
	auto partition = first;
	for (auto iter = first; iter != pivot; ++iter)
	{
		if (*iter <= *pivot)
		{
			std::swap(*partition, *iter);
			++partition;
		}
	}
	std::swap(*partition, *pivot);
	return partition;
}

template <typename Iter>
void QuickSort(Iter begin, Iter end)
{
	if (std::distance(begin, end) > 1)
	{
		auto partitionIter = Partition(begin, end);
		QuickSort(begin, partitionIter);
		QuickSort(partitionIter + 1, end);
	}
}

//The usual way for merge sorted list would be to start from the beginning of the 2 arrays.
//The question we are trying to solve was one around merging the second into the first and
//hence why we have gone from the back of the lists.
template <typename T>
void mergeSortedArrays(std::vector<T>& first, const std::vector<T>& second)
{
	auto originalsize = first.size();
	first.resize(first.size() + second.size());
	auto tail = first.rbegin();
	auto firstTail = first.rbegin() + originalsize;
	auto secondTail = second.rbegin();
	while (firstTail != first.rend() && secondTail != second.rend())
	{
		if (*firstTail > *secondTail)
		{
			*tail++ = *firstTail++;
		}
		else
		{
			*tail++ = *secondTail++;
		}
	}
	while (secondTail != second.rend())
	{
		*tail++ = *secondTail++;
	}
}

template <typename InIter, typename OutIter>
OutIter intersectTwoSortedRanges(InIter begin1, InIter end1, InIter begin2, InIter end2, OutIter start)
{
	while (begin1 != end1 && begin2 != end2)
	{
		if (*begin1 == *begin2)
		{
			*start++ = *begin1;
			++begin1;
			++begin2;
		}
		else if (*begin1 < *begin2)
		{
			++begin1;
		}
		else
		{
			++begin2;
		}
	}
	return start;
}