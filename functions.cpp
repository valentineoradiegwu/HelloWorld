#include "functions.h"
#include <map>
#include <set>
#include <limits.h>
#include <algorithm>
#include <typeinfo>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <memory>

std::vector<int> LeetTwoSum(const std::vector<int>& numbers, int target)
{
	std::vector<int> res{};
	for (int i = 0; i < numbers.size(); ++i)
	{
		for (int j = i + 1; j < numbers.size(); ++j)
		{
			if ((numbers[i] + numbers[j]) == target)
			{
				//why not return at this point?
				return res = { i, j };
			}
		}
	}
	return res;
}

std::vector<int> LeetTwoSum2(const std::vector<int>& numbers, int target)
{
	std::map<int, int> entries;
	std::map<int, int>::iterator item;
	std::vector<int> res{};

	for (int i = 0; i < numbers.size(); ++i)
	{
		auto diff = target - numbers[i];
		item = entries.find(diff);
		if (item != entries.end())
		{
			return res = { item->second, i};
		}
		entries.insert({ numbers[i], i});
	}
	return res;
}

std::vector<int> LeetTwoSumSorted(const std::vector<int>& numbers, int target)
{
	int low = 0;
	int high = numbers.size() - 1;
	std::vector<int> res{};
	while (low < high)
	{
		int sum = numbers[low] + numbers[high];
		if (sum > target)
			--high;
		else if (sum < target)
			++low;
		else
			return {low, high};
	}
	return res;
}

//The solution makes allowance for overflow in the 2 operations
int LeetReverseInt(int input)
{
	int res = 0;
	int a, b, c;
	while (input)
	{
		
		a = (res * 10);
		if (a / 10 != res)
			return 0;
		//std::cout << "res = " << res << ". multiple = " << a << std::endl;
		b = (input % 10);
		c = a + b;
		if ((c - a) != b)
			return 0;
		res = a + b;
		input /=  10;
	}
	return res;
}

int LeetAtoi(const std::string& input)
{
	int res = 0;
	for (auto i = input.begin(); i != input.end(); ++i)
	{
		res = res * 10 + (*i - '0');
	}
	return res;
}

bool LeetIsPalindrome(int x)
{
	int copy = x;
	int reversed = 0;
	int rhs, lhs;
	while (copy)
	{
		rhs = reversed * 10;
		if (rhs / 10 != reversed)
			return false;

		lhs = copy % 10;
		reversed = rhs + lhs;
		if (reversed - rhs != lhs)
			return false;

		copy = copy / 10;
	}
	return x == reversed;
}

int LeetLongestSubstring(const std::string& s)
{
	int i = 0;
	int j = 0;
	int max = 0;
	std::set<char> unique{};
	/*
	1. Keep i and walk with j until u find a char u have seen before. Add to set
	2. If u find a repeating char, increment i, remove i from set.
	*/
	while (j < s.size())
	{
		auto iter = unique.find(s[j]);
		if (iter == unique.end())
		{
			unique.insert(s[j]);
			++j;
			max = std::max(max, j - i);
		}
		else
		{
			//Need to move i until we get to just beyond the repeating char.
			unique.erase(s[i]);
			++i;
		}
	}
	return max;
}

//{ -1, 0, 1, 2, -1, -4 }
std::vector<std::vector<int> > LeetThreeSum(std::vector<int>& nums)
{
	std::vector<std::vector<int> > res{};

	if (nums.size() < 3)
		return res;

	std::sort(nums.begin(), nums.end());
	int sum = 0;

	for (size_t i = 0; i < nums.size(); ++i)
	{
		for (size_t j = i + 2; j < nums.size(); ++j)
		{
			sum = nums[i] + nums[i + 1] + nums[j];
			if ( sum == 0)
			{
				std::cout << nums[i] << "," << nums[i + 1] << "," << nums[j] << std::endl;
				res.push_back({ nums[i], nums[i + 1], nums[j]});
			}

		}
	}
	return res;
}

void reverseFunc(char* input)
{
	size_t len = strlen(input);
	if (len)
	{
		char* start = input;
		char* end = input + len - 1;
		for (; start < end; ++start, --end)
		{
			char temp = *start;
			*start = *end;
			*end = temp;
		}
	}
}

int Factorial(int i)
{
	if (i == 1)
	{
		return 1;
	}
	else
	{
		return i * Factorial(i - 1);
	}
}

bool unique_chars(const char* input)
{
	bool chars[256] = { false };
	for (const char* i = input; *i != '\0'; ++i)
	{
		if (chars[*i])
			return false;
		chars[*i] = true;
	}
	return true;
}

bool unique_chars2(const char* input)
{
	const char* head = input;
	for(const char* i = ++input; *i; ++i)
	{
		for (const char* j = head; j != i; ++j)
			if (*j == *i)
				return false;
	}
	return true;
}

//This doesnt preserve the original ordering
//Basically ensures that the remaining is a set and in a set positioning is irrelevant
void remove_dupes(char* input)
{
	size_t len = strlen(input);
	char* tail = input + len - 1;

	for (char* i = input; i <= tail; ++i)
	{
		for (char* j = i + 1; j <= tail; )
		{
			if (*i == *j)
			{
				*j = *tail;
				--tail;
			}
			else
			{
				++j;
			}
		}
	}
	*(++tail) = '\0';
}

//Having an extra array for the algo means that it basically simplifies to a std::remove_if
void remove_dupes2(char* input)
{
	bool seen[256] = { false };
	char* tail = input;
	for (char* i = input; *i; ++i)
	{
		if (!seen[*i])
		{
			*tail = *i;
			++tail;
			seen[*i] = true;
		}
	}
	*tail = '\0';
}

void remove_dupes3(char* input)
{
	char* tail = input + 1;
	for (char* i = input + 1; *i; ++i)
	{
		char* j = input;
		for (; j != tail; ++j)
		{
			if (*j == *i) break;
		}
		if (j == tail)
		{
			*tail = *i;
			++tail;
		}
	}
	*tail = '\0';
}
/*
ANagrams
1. Sort the 2 strings and compare the strings fr equality. If equal, then they are anagrams.
2. Build a map of chars to occurences in first string. Then decrease the occurences in second string and the map should have all zeros if an anagram.
3. SImilar to (2) but rather than comparing the map of chars to occurences to be all 0's, we can also track a count of chars and that should be 0 at end of second string.
*/
bool are_anagrams(const char* input1, const char* input2)
{
	if (strlen(input1) != strlen(input2))
		return false;
	int letters[256] = { 0 };
	int unique_chars = 0;

	for (const char* i = input1; *i; ++i)
	{
		if (!letters[*i])
			++unique_chars;
		++letters[*i];
	}

	for (const char* i = input2; *i; ++i)
	{
		if (letters[*i] == 0)
			return false;

		--letters[*i];

		if (letters[*i] == 0)
			--unique_chars;
		if (unique_chars == 0)
			return *(++i) == '\0';
	}
	return false;
}

std::string replaceSpaceWithEncoding(char* input)
{
	int spaceCount = 0;
	for (char* i = input; *i; ++i)
	{
		if (*i == ' ')
			++spaceCount;
	}
	const int length = strlen(input);
	const int newLength = length + (spaceCount * 2);
	char* newString = new char [newLength];
	//auto newString = std::make_unique<char[]>(newLength);
	newString[newLength] = '\0';

	char* lastElement = input + (length - 1);
	char* lastElementNew = newString + (newLength - 1);
	for (char* i = lastElement; i >= input; --i)
	{
		if (*i == ' ')
		{
			*lastElementNew = '0';
			--lastElementNew;
			*lastElementNew = '2';
			--lastElementNew;
			*lastElementNew = '%';
			--lastElementNew;
		}
		else
		{
			*lastElementNew = *i;
			--lastElementNew;
		}
	}
	auto res = std::string(newString);
	//delete[] newString;
	return res;

}

/*
1. Traverse the 2 dim array recording every row or column that has a 0.
2. Traverse the 2 dim array again and if a cell falls in a row or column with a zero, set it to 0.
*/
void setZeros(int matrix[4][4])
{
	//constexpr int rows = sizeof matrix / sizeof matrix[0];
	//constexpr int cols = std::extent<decltype(matrix), 1>::value;
	int rows_with_zeros[4] = { 1 };
	int columns_with_zeros[4] = { 1 };

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (matrix[i][j] == 0)
			{
				rows_with_zeros[i] = 0;
				columns_with_zeros[j] = 0;
			}
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (rows_with_zeros[i] == 0 || columns_with_zeros[j] == 0)
			{	
				matrix[i][j] = 0;
			}
		}
	}
}

int myStrCmp(const char* input1, const char* input2)
{
	while (*input1)
	{
		if (!*input2)
			return 1;
		if (*input1 > *input2)
			return 1;
		if (*input1 < *input2)
			return -1;
		++input1;
		++input2;
	}

	if (*input2)
		return -1;

	return 0;
}

// If the string is boomboomboomd, will your algorithm return true for a substring boomboomd?
bool is_substr(const char* input1, const char* input2)
{
	//obviously u should check if the length ofsubstring satisfies a few considerations
	//this code may be easier if i used strlen but trying to avoid that cost.
	for (const char* i = input2; *i; ++i)
	{
		if (*i == *input1)
		{
			const char* sub = input1 + 1;
			const char* super = i + 1;
			while (*sub)
			{
				if (!*super)
					return false;
				if (*sub != *super)
					break;
				++sub;
				++super;
			}
			if (!*sub)
			    return true;
		}
	}
	return false;
}

int UtopianTree(int cycles)
{
	int height = 1;
	for (int i = 1; i <= cycles; ++i)
	{
		if (i % 2 == 0)
		{
			height = height + 1;
		}
		else
		{
			height = 2 * height;
		}
	}
	return height;
}

std::vector<std::vector<int> > LeetThreeSum2(std::vector<int>& nums)
{
	std::vector<std::vector<int> > res{};

	if (nums.size() < 3)
		return res;

	std::sort(nums.begin(), nums.end());
	int sum = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int start = 0;
	int end = nums.size() - 1;

	for (size_t i = 0; i < nums.size() - 2; ++i)
	{
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		start = i + 1;
		a = nums[i];
		while (start < end)
		{
			if (start > i + 1 && nums[start] == nums[start - 1])
			{
				++start;
				continue;
			}
			b = nums[start];
			c = nums[end];
			sum = a + b + c;
			if (sum == 0)
			{
				std::cout << a << "," << b << "," << c << std::endl;
				res.push_back({ a, b, c });
				--end;
				++start;
			}
			else if (sum > 0)
			{
				--end;
			}
			else
			{
				++start;
			}

		}
	}
	return res;
}

int myAtoi(std::string str) 
{
	int res = 0;
	int sign = 1;
	bool seen_first_non_whitespace = false;
	for (auto character : str)
	{
		if (character == ' ' && !seen_first_non_whitespace)
		{
			continue;
		}

		if (!seen_first_non_whitespace)
		{
			seen_first_non_whitespace = true;
			if (character == '-' || character == '+')
			{
				if (character == '-')
					sign = -1;
				continue;
			}
		}

		if (character < '0' || character > '9')
			break;

		res = (res * 10) + (character - '0');
	}
	return sign * res;
}

std::vector<std::string> stringToVector(const std::string& input)
{
	std::vector<std::string> strings;
	std::istringstream f{input};
	std::string each_token;
	while (getline(f, each_token, ' ')) {
		std::cout << each_token << std::endl;
		strings.push_back(each_token);
	}
	return strings;
}

bool IsSentenceInString(const std::string& ransom, const std::string& dictionary)
{
	auto ransom_words = stringToVector(ransom);
	auto dictionary_words = stringToVector(dictionary);
	std::map<const std::string, int> freq;
	for (auto& word : dictionary_words)
	{
		++freq[word];
	}
	for (auto& word : ransom_words)
	{
		if (freq.find(word) == freq.end() || freq[word] == 0)
			return false;
		else
			--freq[word];
	}
	return true;
}

template <typename T>
std::string getType(const T& arg)
{
	const std::type_info& ti = typeid(arg);
	return ti.name();
}

template std::string getType<int>(const int& arg);