#include "functions.h"
#include <map>
#include <set>
#include <limits.h>
#include <algorithm>
#include <typeinfo>
#include <string.h> 

std::vector<int> LeetTwoSum(const std::vector<int>& numbers, int target)
{
	std::vector<int> res{};
	for (int i = 0; i < numbers.size(); ++i)
	{
		for (int j = i + 1; j < numbers.size(); ++j)
		{
			if ((numbers[i] + numbers[j]) == target)
			{
				res = { i, j };
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
			return res = { i, item->second};
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
		input = input / 10;
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

//calculus
int LeetLongestSubstring(const std::string& s)
{
	int longest = 0;
	int current = 0;
	int i = 0;
	bool allUnique = true;
	std::map<char, int> seen;
	std::map<char, int>::iterator found;

	resume:
	for (; i < s.size(); ++i)
	{
		found = seen.find(s[i]);
		if (found == seen.end())
		{
			++current;
			seen.insert({ s[i], i });
		}
		else
		{
			allUnique = false;
			i = found->second + 1;
			seen.clear();
			if (current > longest)
			{
				longest = current;
			}
			current = 0;
			goto resume;
		}
	}

	return allUnique? s.size(): (current > longest) ? current: longest;
}

//{ -1, 0, 1, 2, -1, -4 }
std::vector<std::vector<int> > LeetThreeSum(std::vector<int>& nums)
{
	std::vector<std::vector<int> > res{};

	if (nums.size() < 3)
		return res;

	std::sort(nums.begin(), nums.end());
	int sum = 0;

	for (int i = 0; i < nums.size(); ++i)
	{
		for (int j = i + 2; j < nums.size(); ++j)
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
		{
			return false;
		}
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
		if (!letters[*i])
			return false;

		--letters[*i];

		if (!letters[*i])
			--unique_chars;
		if (!unique_chars)
		{
			return !*(++i);
		}
	}
	return false;
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

	for (int i = 0; i < nums.size() - 2; ++i)
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

template <typename T>
std::string getType(const T& arg)
{
	const std::type_info& ti = typeid(arg);
	return ti.name();
}

template std::string getType<int>(const int& arg);