#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>      // std::invalid_argument

std::vector<int> LeetTwoSum(const std::vector<int>& numbers, int target);
std::vector<int> LeetTwoSum2(const std::vector<int>& numbers, int target);
std::vector<int> LeetTwoSumSorted(const std::vector<int>& numbers, int target);
int LeetReverseInt(int input);
int LeetAtoi(const std::string& input);
bool LeetIsPalindrome(int x);
int LeetLongestSubstring(const std::string& s);
std::vector<std::vector<int> > LeetThreeSum(std::vector<int>& nums);
std::vector<std::vector<int> > LeetThreeSum2(std::vector<int>& nums);
void reverseFunc(char* input);
int Factorial(int i);
bool unique_chars(const char* input);
bool unique_chars2(const char* input);
void remove_dupes(char* input);
void remove_dupes2(char* input);
void remove_dupes3(char* input);
void setZeros(int matrix[][4]);
int myStrCmp(const char* input1, const char* input2);
bool are_anagrams(const char* input1, const char* input2);
std::string replaceSpaceWithEncoding(char* input);
bool is_substr(const char* input1, const char* input2);
int UtopianTree(int cycles);
int myAtoi(std::string str);
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


template <typename Iter, typename T>
bool binary_search(Iter begin, Iter end, T key)
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