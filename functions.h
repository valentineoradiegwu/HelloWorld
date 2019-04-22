#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>      // std::invalid_argument
#include <iterator>
#include <stack>
#include <map>
#include <functional>
#include <numeric>

std::vector<int> LeetTwoSum(const std::vector<int>& numbers, int target);
std::vector<int> LeetTwoSum2(const std::vector<int>& numbers, int target);
std::vector<int> LeetTwoSumSorted(const std::vector<int>& numbers, int target);
std::vector<std::pair<int, int>> twoSumSortedAllMatches(const std::vector<int>& nums, int target);
int LeetReverseInt(int input);
int LeetAtoi(const std::string& input);
bool LeetIsPalindrome(int x);
int LeetLongestSubstring(const std::string& s);
std::vector<std::vector<int> > LeetThreeSum(std::vector<int>& nums);
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
void reverse(char* input, char* end);
void reverseWords(char* input);
std::string MergeStrings(const std::vector<std::string>& iInput);
bool IsSentenceInString(const std::string& ransom, const std::string& dictionary);
bool IsSentenceInString2(const std::string& ransom, const std::string& dictionary);
void setZeros(int matrix[][4]);
int myStrCmp(const char* input1, const char* input2);
bool are_anagrams(const char* input1, const char* input2);
bool are_anagrams2(const std::string& one, const std::string& two);
std::vector<std::vector<std::string>> Anagrams(const std::vector<std::string>& dictionary);
std::string replaceSpaceWithEncoding(char* input);
int BinSearchArray(int input[], int length, int key);
std::pair<int, int> FindLargestIncreasingSubSequence(const std::vector<int>& input);
bool is_substr(const char* input1, const char* input2);
int UtopianTree(int cycles);
int myAtoi(std::string str);
int fib(int n);
int fibr(int n);
size_t CountBitsInInt(int input);
int squareRoot(int input);
int squareRoot2(int input);
int binSearchFirstOccurence(const std::vector<int>& input, int key);
int BinFindFirstLargerThanK(const std::vector<int>& input, int key);
std::string multiplyStrings(const std::string& first, const std::string& second);
std::map<int, int> coinChange(std::vector<int>& denominations, int amount);
int FindMaxLengthValidParenthesis(const std::string& input);
int firstRepeatingInteger(const std::vector<int>& input);
int searchNumOccurrenceR(const std::vector<int>& input, int k, int start, int end);
std::vector<int> rotateArray(const std::vector<int>& input, int step);
void addOneToVector(std::vector<int>& input);
int coverPoints(const std::vector<int>& A, const std::vector<int>& B);
std::vector<int> repeatedAndDuplicateNumber(const std::vector<int>& input);
std::vector<std::pair<int, int>> mergeInterval(std::vector<std::pair<int, int>>& intervals);
std::vector<std::pair<int, int>> insertAndMergeInterval(std::vector<std::pair<int, int>>& intervals, std::pair<int, int> newInterval);
std::vector<std::pair<int, int>> insertAndMergeInterval2(std::vector<std::pair<int, int>>& intervals, std::pair<int, int> newInterval);
int repeatedNumberModify(std::vector<int>& input);
/*
You are designing a compiler for a C++ program and need to check that braces in any file are balanced.
Braces in a string are considered balanced if the following criteria are met.
1. All braces must be close. Braces come in pairs of the form {}, () and []. The left brace opens the pair the right one closes it.
2. In any set of nested braces, the braces between any pair must be closed.
For example, [{}] is valid but [}]{} is not.

Note that each string is composed entirely of '{' , '}' , '(' , ')' , '[' and ']'.

Function Description:
Complete the fuction braces in the editor below. The function must return an array of strings where the string at each index denotes
whether the braces were balanced in the corresponding index of the input. Return a YES for balanced and NO for not balanced
*/
std::vector<std::string> braces(const std::vector<std::string>& input);
bool is_balanced(const std::string& word);
bool is_balanced_can_contain_nonbraces(const std::string& word);
/*
You just got a new job where you have to work exactly as many hours as you are told each week. Some of the days, they tell you how many
hours you will work. You get to choose the remainder of your schedule within the limits.

A completed schedule consist of exactly 7 digits in the range 0 to 8 representing each day's hours to be worked. You will get a pattern 
string for the scheule, but with some of the replaced by a question mark, ?, (ascii 63 decimal). Given a maximum number of hours you can work in a day, 
replace the question marks with digits so that the sum of the scheduled hours is exactly the hours you must work in a week. Return a string array
with all possible schedules you can create, ordered lexicographically.

For example, your partial schedule pattern = 08??840, your required hours, work_hours = 24, and you can only work at most, day_hours =4 hours
per dayduring the 2 days in question. You have two days on which you must work 24 - 20 = 4 more hours for the week. All of your possible schedules are listed below;

0804840
0813840
0822840
0831840
0840840

Function Description: 
Complete the function findSchedules in the editor below. The function must return an array of strings that represents all the possible valid schedules. The strings 
must be ordered lexicographically

findSchedules has the following parameters;
work_hours: an integer that represents the hours you must work in the week.
day_hours: an onteger that represents the maximum hours you may work in a day.
patter: a string that represents the partially completed schedule.
*/

std::vector<std::string> findSchedules(int work_hours, int day_hours, const std::string& pattern);
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

/*template <typename CONT>
std::ostream& operator<<(std::ostream& os, const CONT& container)
{
	auto sep = " ";
	os << "[";
	for (auto item : container)
	{
		os << sep << item;
		sep = " ;"
	}
	os << "]";
	return os;
}*/

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, const std::pair<T1, T2>& pair)
{
	os << "First = " << pair.first << " . Second = " << pair.second;
	return os;
}

template <typename T>
std::string getType(const T&);

template <typename T>
T secondMax(const std::vector<T>& input)
{
	if input.empty()
		throw std::invalid_argument{ "The input must have at least one value" };
	T max = input[0];
	T secondmax = input[0];
	for (auto i : input)
	{
		if (i > max)
		{
			secondmax = max;
			max = i;
		}
		else if (i > secondmax)
		{
			secondmax = i;
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
		while (current > begin && *current < *(current - 1))
		{
			std::swap(*current, *(current - 1));
			--current;
		}
		++start;
	}
}

template <typename T>
void InsertionSort(std::vector<T>& input)
{
	for (auto i = 0; i < input.size(); ++i)
	{
		auto j = i;
		while (j > 0 && input[j] < input[j - 1])
		{
			std::swap(input[j], input[j - 1]);
			j--;
		}
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