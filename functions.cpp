#include "functions.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <limits.h>
#include <algorithm>
#include <typeinfo>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <memory>
#include <functional>

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
	1. Keep i and walk with j until u find a char u have seen before and add to set as u go along
	2. If u find a repeating char, increment i, remove i from set.
	*/
	while (j < s.size())
	{
		if (unique.find(s[j]) == unique.end())
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

int FindMaxLengthValidParenthesis(const std::string& input)
{
	std::stack<int> stk{};
	stk.push(-1);
	int res = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == '(')
			stk.push(i);
		else
		{
			stk.pop();
			if (!stk.empty())
				res = std::max(res, i - stk.top());
			else
				stk.push(i);
		}
	}
	return res;
}

int firstRepeatingInteger(const std::vector<int>& input)
{
	std::unordered_set<int> unique{};
	for (auto i : input)
	{
		auto result = unique.insert(i);
		if (!result.second)
			return i;
	}
	assert(false);
}

/*
1. To rotate an array by an offset, you want to start from the offset and wrap around
2. You probably want to add an optimization. If the offset to rotate by a multiple of the size,
   just bail out.
*/
std::vector<int> rotateArray(const std::vector<int>& input, int step) {
	if (step % input.size() == 0)
		return input;

	std::vector<int> ret;
	ret.reserve(input.size());

	for (int i = 0; i < input.size(); i++) 
		ret.push_back(input[(i + step) % input.size()]);
	return ret;
}

//What will be your base case bruv?
int searchNumOccurrenceR(const std::vector<int>& input, int k, int start, int end)
{
	if (start > end) return 0;

	int mid = start + (end - start) / 2;

	if (input[mid] < k) return searchNumOccurrenceR(input, k, mid + 1, end);
	else if (input[mid] > k) return searchNumOccurrenceR(input, k, start, mid - 1);
	else return searchNumOccurrenceR(input, k, start, mid - 1) + 1 + searchNumOccurrenceR(input, k, mid + 1, end);
}

//In place?
//An optimisation would be to check the last value. if it is less than than 9
//add 1 to it and return.
void addOneToVector(std::vector<int>& input)
{
	if (input.empty())
		return;

	auto nonZero = input.begin();
	for (auto i = input.begin(); i != input.end(); ++i)
	{
		if (*i != 0)
		{
			nonZero = i;
			break;
		}
	}

	if (nonZero != input.begin())
		input.erase(input.begin(), nonZero);

	int carry = 0;
	int add = 1;

	auto last = input.rbegin();
	if (*last < 9)
	{
		*last += add;
		return;
	}

	for (auto i = input.rbegin(); i != input.rend(); ++i)
	{
		int sum = *i + add + carry;
		carry = sum / 10;
		*i = sum % 10;
		add = 0;
	}
	if (carry)
		input.insert(input.begin(), carry);
	return;
}

int coverPoints(const std::vector<int>& A, const std::vector<int>& B) {
	int count = 0;
	if (A.empty() || B.empty())
		return count;
	int currX = A[0];
	int currY = B[0];
	for (int i = 1; i < A.size(); ++i)
	{
		int nextX = A[i];
		int nextY = B[i];
		count += std::max(std::abs(nextX - currX), std::abs(nextY - currY));
		currX = nextX;
		currY = nextY;
	}
	return count;
}

//{ -1, 0, 1, 2, -1, -4 }
std::vector<std::vector<int> > LeetThreeSum(std::vector<int>& nums)
{
	std::vector<std::vector<int> > res{};

	if (nums.size() < 3)
		return res;

	std::sort(nums.begin(), nums.end());
	auto const size = nums.size();
	for (int i = 0; i < nums.size() - 2; ++i)
	{
		if (i > 0 && nums[i] == nums[i - 1])
			continue;

		auto low = i + 1;
		auto high = size - 1;
		auto two_sum_target = 0 - nums[i];

		while (low < high)
		{
			auto sum = nums[low] + nums[high];
			if (sum == two_sum_target)
			{
				std::vector<int> aResult{ nums[i], nums[low], nums[high] };
				res.push_back(aResult);
				++low;
				--high;
				while (low < high && nums[low] == nums[low - 1])
					++low;
				while (low < high && nums[high] == nums[high + 1])
					--high;
			}
			else if (sum < two_sum_target)
				++low;
			else
				--high;
		}

	}
	return res;
}

//right appears redundant. Can be substituted by i
std::pair<int, int> FindLargestIncreasingSubSequence(const std::vector<int>& input)
{
	if (input.empty())
		return{ 0, 0 };

	int left = 0;
	int right = 0;
	int leftMax = 0;
	int rightMax = 0;

	for (auto i = 1; i < input.size(); ++i)
	{
		if (input[i] > input[i - 1])
		{
			right = i;
			if ((right - left + 1) > (rightMax - leftMax + 1))
			{
				leftMax = left;
				rightMax = right;
			}
		}
		else
		{
			left = i;
		}
	}
	return { leftMax, rightMax };
}

std::vector<std::pair<int, int>> twoSumSortedAllMatches(const std::vector<int>& nums, int target)
{
	std::vector<std::pair<int, int>> res{};
	if (nums.empty())
		return res;

	auto low = 0;
	auto high = nums.size() - 1;

	while (low < high)
	{
		//Take care of non-uniques
		//An alternative is to use 2 extra while loops to advance low and high thereby exhausting
		//the duplicates
		const auto isLowSameAsPrev = low > 0 && nums[low] == nums[low - 1];
		const auto isHighSameAsPrev = high < nums.size() - 1 && nums[high] == nums[high + 1];
		if (isLowSameAsPrev || isHighSameAsPrev)
		{
			if (isLowSameAsPrev)
			{
				++low;
			}
			if (isHighSameAsPrev)
			{
				--high;
			}
			continue;
		}
	
		auto sum = nums[low] + nums[high];
		if (sum == target)
		{
			res.push_back({ low, high });
			++low;
			--high;
		}
		else if (sum > target)
			--high;
		else
			++low;
	}
	return res;
}


int LeetsubarraySum(std::vector<int>& nums, int k) 
{
	auto res = 0;
	auto sum = 0;
	std::unordered_map<int, int> prevSums;
	for (auto i : nums)
	{
		sum += i;
		if (sum == k)
			++res;
		if (prevSums.find(sum - k) != prevSums.end())
			res += prevSums[sum - k];
		prevSums[sum]++;
	}
	return res;
}

/*
There are probably 2 ways to play this. 
1. We store the sum at each index against its index in a map. Only store if we are seing for first time since we want the maximum length so the more left the better
2. During each iter we check if the current sum minus k already exists. If it does we have a subarray then move to 3. 
3. check the difference btw current index and index stored against its compliment
 During
*/
int LeetMaximumSubarraySum(std::vector<int>& nums, int k)
{
	auto maxLength = 0;
	auto sum = 0;
	std::unordered_map<int, int> prevSums;
	prevSums.insert({ sum, -1 });
	for (auto i = 0; i < nums.size(); ++i)
	{
		sum += nums[i];
		auto complement = prevSums.find(sum - k);
		if (complement != prevSums.end())
			maxLength = std::max(maxLength, i - complement->second);
		prevSums.insert({sum, i});
	}
	return maxLength;
}

/*
You are given an array A containing 2*N+2 positive numbers, out of which 2*N numbers exist in pairs whereas the other two number occur exactly once and are distinct. 
You need to find the other two numbers and print them in ascending order.
*/
void PrintDistinctNumbersWithPairs(std::vector<int>& nums)
{
	std::map<int, int> freqs;
	for (int i : nums)
	{
		freqs[i]++;
	}
	for (auto& iter : freqs)
	{
		if (iter.second == 1)
			std::cout << iter.first << std::endl;
	}
}

void PrintDistinctNumbersWithPairs1(std::vector<int>& nums)
{
	std::sort(nums.begin(), nums.end());
	auto begin = nums.begin();
	while (begin < nums.end())
	{
		auto next = begin + 1;

		if (next == nums.end() || *begin != *next)
		{
			//If next is end then begin is the last element
			//If next is not equal to current then we are a solitary element.
			std::cout << *begin << std::endl;
			++begin;
		}
		else
		{
			begin += 2;
		}

	}
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

void reverse(char* input, char* end)
{
	if (!input)
		return;

	char* start = input;
	for (; start < end; ++start, --end)
	{
		std::swap(*start, *end);
	}
}

void reverseWords(char* input)
{
	auto len = strlen(input);
	reverse(input, input + len - 1);
	char* left = input;
	char* right = input;
	char* end = input + len;
	for (; right <= end; ++right)
	{
		if (*right == ' ' || *right == '\0')
		{
			reverse(left, right - 1);
			left = right + 1;
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

size_t CountBitsInInt(int input)
{
	size_t count = 0;
	while (input > 0)
	{
		if ((input & 1) == 1) ++count;
		input >>= 1;
	}
	return count;
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

bool are_anagrams2(const std::string& one, const std::string& two)
{
	if (one.size() != two.size())
		return false;

	int map[256] = { 0 };
	int unique_chars = 0;

	for (char eachChar : one)
	{
		if (map[eachChar] == 0)
			++unique_chars;
		map[eachChar]++;
	}

	for (auto i = 0; i < two.size(); ++i)
	{
		if (map[two[i]] == 0)
			return false;
		--map[two[i]];
		if (map[two[i]] == 0)
			--unique_chars;
		if (unique_chars == 0)
			return (i == two.size() - 1);
	}
	return false;
}

/*
Given a dictionary of English words, return the set of all words grouped into 
set of words that are anagrams.
*/

std::vector<std::vector<std::string>> Anagrams(const std::vector<std::string>& dictionary)
{
	std::unordered_map<std::string, std::vector<std::string>> words{};
	std::vector<std::vector<std::string>> res{};
	for (const auto& eachWord : dictionary)
	{
		std::string key{ eachWord };
		std::sort(key.begin(), key.end());
		words[key].push_back(eachWord);
	}

	for (const auto& pair : words)
	{
		if (pair.second.size() > 1)
			res.push_back(pair.second);
	}
	return res;
}

std::vector<std::string> braces(const std::vector<std::string>& input)
{
	const auto len = input.size();
	std::vector<std::string> result(len, "NO");
	for (auto i = 0; i < len; ++i)
		if (is_balanced(input[i]))
			result[i] = "YES";
	return result;
}

bool is_balanced(const std::string& word)
{
	std::stack<char> stk{};
	for (char bracket : word)
	{
		switch (bracket)
		{
		case '{': stk.push('}'); break;
		case '[': stk.push(']'); break;
		case '(': stk.push(')'); break;
		default: 
			if (stk.empty() || stk.top() != bracket) { return false; }
			stk.pop();
		}
	}
	return stk.empty();
}
//if i am terminating brace then 
// If stack is empty return false
// if top of stack is not me return false
// else continue to next char.
bool is_balanced_can_contain_nonbraces(const std::string& word)
{
	std::stack<char> stk{};
	auto is_terminating_brace = [](char c) {return c == '}' || c == ']' || c == ')'; };
	for (char eachChar : word)
	{
		switch (eachChar)
		{
		case '{': stk.push('}'); break;
		case '[': stk.push(']'); break;
		case '(': stk.push(')'); break;
		default:
			if (is_terminating_brace(eachChar))
			{
				if (stk.empty() || stk.top() != eachChar)
				{
					return false;
				}
				stk.pop();
			}
		}
	}
	return stk.empty();
}

/*
pattern = 08??840
0804840
0813840
0822840
0831840
0840840
*/

std::vector<std::vector<int>> Permutations(int hrs_outstanding, int day_hours, std::vector<int> index_for_missing_days)
{
	int missing_days = index_for_missing_days.size();
	//Generate permutations from 0 to day_hours of size missing_days
	std::vector<int> range(day_hours + 1);
	for (int i = 0; i < range.size(); ++i)
		range[i] = i;
	std::vector<std::vector<int>> permutations{};

	//Some high school permutation computations. I had to look this up on the internet
	//as its being quite a while I did it last.
	int no_of_permutations = std::pow(range.size(), index_for_missing_days.size());

	for (int i = 0; i < no_of_permutations; ++i)
	{
		std::vector<int> permutation{};
		for (int j = 0; j < index_for_missing_days.size(); ++j)
		{
			int selector = static_cast<int>(i / std::pow(range.size(), j)) % range.size();
			permutation.push_back(range[selector]);
		}
		permutations.push_back(std::move(permutation));
	}

	//Filter off permutations which do not tally up to the outstanding hours.
	permutations.erase(std::remove_if(permutations.begin(),
		permutations.end(),
		[hrs_outstanding](const std::vector<int>& x) {return std::accumulate(x.begin(), x.end(), 0) != hrs_outstanding; }), permutations.end());
	return permutations;
}

std::vector<std::string> findSchedules(int work_hours, int day_hours, const std::string& pattern)
{
	int total_hours_in_pattern = 0;
	std::vector<int> index_for_missing_days{};
	for (int i = 0; i < pattern.size(); ++i)
	{
		if (pattern[i] == '?')
			index_for_missing_days.push_back(i);
		else
			total_hours_in_pattern += pattern[i] - '0';
	}

	int hrs_outstanding = work_hours - total_hours_in_pattern;
	auto permutations = Permutations(hrs_outstanding, day_hours, index_for_missing_days);
	std::vector<std::string> res{};

	//We need to interpolate the hrs from the permutation into the ? in schedule
	//We know the indexes where the ? are in the schedule since we stored them in index_for_missing_days
	for (const auto & permutation : permutations)
	{
		std::string schedule{ pattern };
		for (int i = 0; i < permutation.size(); ++i)
		{
			int time = permutation[i];
			schedule[index_for_missing_days[i]] = '0' + time;
		}
		res.push_back(schedule);
	}
	//Is there a way to ensure the algo in Permutations guarantees its results in sorted order
	//and therefore make the nlogn sort unnecessary?
	std::sort(res.begin(), res.end());
	return res;
}

std::map<int, int> coinChange(std::vector<int>& denominations, int amount)
{
	std::map<int, int> res{};
	int pendingAmount = amount;
	//The denominations need to be sorted in reverse
	//This also has to be a set i.e no dupes
	std::sort(denominations.rbegin(), denominations.rend());
	for (auto denomination : denominations)
	{
		if (denomination > pendingAmount)
			continue;
		//multiples is guaranteed to be at least 1 here
		int multiples = pendingAmount / denomination;
		res.insert({denomination, multiples});
		pendingAmount = pendingAmount - (multiples * denomination);
		if (pendingAmount == 0)
			return res;
	}
	throw std::invalid_argument{"Could not find complete change for the amount " + amount};
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
		if (*input2 < *input1)
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

// If the string is boomboomboomd, will your algorithm return true for a substring boomboomd? It does but may be suboptimal.
// The Boyer-Moore string search algo appears to be the fastest theoretically.
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

int BinSearchArray(int input[], int length, int key)
{
	int low = 0;
	int high = length - 1;

	while (low <= high)
	{
		int middle = low + (high - low) / 2;
		if (input[middle] == key)
			return middle;
		else if (input[middle] < key)
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;
}

// 1. If we find a match at mid and the previous field is not equal to us, then we are the first occurence. Return index.
// 2. If we find a match but the prev field is equal to us, then we treat as if the mid point is greater so we move high left.
// 1, 2, 3, 3, 3, 3, 4
int binSearchFirstOccurence(const std::vector<int>& input, int key)
{
	int low = 0;
	int high = input.size() - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (input[mid] == key && (mid == 0 || input[mid - 1] != input[mid]))
			return mid;
		else if (input[mid] >= key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

int BinFindFirstLargerThanK(const std::vector<int>& input, int key)
{
	int left = 0;
	int right = input.size() - 1;
	while (left != right)
	{
		int mid = left + (right - left) / 2;
		if (input[mid] <= key)
			left = mid + 1;
		else
			right = mid;
	}
	return left == input.size() ? -1 : left;
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

std::string MergeStrings(const std::vector<std::string>& iInput)
{
	char myArray[26] = { 0 };
	for (auto& eachString : iInput)
	{
		for (auto eachChar : eachString)
		{
			myArray[eachChar - 'a']++;
		}
	}

	std::string result;
	for (int i = 0; i < 26; ++i)
	{
		if (myArray[i] > 0)
			result.append(myArray[i], 'a' + i);
	}
	return result;
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

//This is done in a character by character basis rather than a word by word basis as above.
bool IsSentenceInString2(const std::string& letter, const std::string& magazine)
{
	int chars[256] = { 0 };
	for (auto c : magazine)
		++chars[c];
	for (auto c : letter)
	{
		if (chars[c] > 0)
		{
			--chars[c];
		}
		else
			return false;
	}
	return true;
}
//You need to know how hash maps work out the index to store a key to understand this solution
//There are a few variations to the problem and one is to find the smallest +ve number. I think we 
//will go for that.
int missing_integer(std::vector<int> input)
{
	std::vector<int> bitVector(input.size() + 1);
	for (auto i : input)
	{
		if(i > 0)
			bitVector[i % (input.size() + 1)] = 1;
	}

	for (auto i = 0; i < bitVector.size(); ++i)
	{
		if (bitVector[i] == 0)
			return i;
	}
	return -1;
}

int fib(int n)
{
	if (n <= 1)
		return 1;

	int prev = 0;
	int current = 1;
	int fib = 0;

	for (int i = 1; i < n; ++i)
	{
		fib = current + prev;
		prev = current;
		current = fib;
	}
	return fib;
}

int squareRoot(int input)
{
	int i = 1;
	int res = i * i;
	while (res <= input)
	{
		++i;
		res = i * i;
	}
	return i - 1;
}

int squareRoot2(int input)
{
	int low = 0;
	int high = input;
	int res;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (mid * mid == input)
		{
			return mid;
		}
		else if (mid * mid > input)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
			res = mid;
		}
	}
	return res;
}

// When subtracting from a size_t, u have to be careful.
// 0 - 1 where 0 is held in size_t results in a very large int and not -1
// Becareful with your use of auto as a variable maybe declared size_t without u knowing.
std::string multiplyStrings(const std::string& first, const std::string& second)
{
	const auto sizeFirst = first.size();
	const auto sizeSecond = second.size();
	std::string result( sizeFirst + sizeSecond , '0');

	for (int i = sizeFirst - 1; i >= 0; --i)
	{
		int carry = 0;
		for (int j = sizeSecond - 1; j >= 0; --j)
		{
			const int idx = i + j + 1;
			int mult = (first[i] - '0') * (second[j] - '0') + carry + (result[idx] - '0');
			result[idx] = mult % 10 + '0';
			carry = mult / 10;
		}
		result[i] += carry;
	}

	const auto startpos = result.find_first_not_of("0");
	if (std::string::npos != startpos)
		return result.substr(startpos);
	return "0";
}

template <typename T>
std::string getType(const T& arg)
{
	const std::type_info& ti = typeid(arg);
	return ti.name();
}

template std::string getType<int>(const int& arg);