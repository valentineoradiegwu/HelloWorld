#pragma once
#include <vector>
#include <iostream>

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
int myStrCmp(const char* input1, const char* input2);
bool are_anagrams(const char* input1, const char* input2);
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