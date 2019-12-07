// Example program
#include <string>
#include <vector>
#include <cstdlib>
#include <boost/foreach.hpp>
#include "functions.h"
#include "producerconsumer.h"
#include "produce1consume1.h"
#include "MyTree.h"
#include "mylist.h"
#include "mystack.h"
#include <thread>
#include "mytemplates.h"
#include "printtuple.h"
#include "LRUCache.h"
#include "SetOfStacks.h"
#include <memory>
#include <climits>
#include <iterator>
#include "ParallelAccumulate.h"
#include "ThreadSafeList.h"
#include "ThreadSafeQueue.h"
#include "rep_client.h"
#include "rep_server.h"
#include "ThreadPool.h"
#include "HierarchicalObject.h"
#include "my_mem_fn.h"
#include "vending_machine.h"
#include "type_erasure.h"

void hello()
{
	std::cout << "Hello Concurrent World\n";
}

void recursive_reverse(const char* input, std::string& output)
{
	if (*input == '\0')
		return;
	output = *input + output;
	recursive_reverse(++input, output);
}

std::string recursive_reverse2(const std::string& input)
{
	if (input.empty())
		return "";

	return recursive_reverse2(input.substr(1)) + input[0];
}

int main()
{
	/**auto stuff = 1;
	std::vector<int> num {1,2,3,4};
	for (auto& i : num)
		std::cout << i << "!\n";

	std::string hello("Hello, world!");

	BOOST_FOREACH(char ch, hello)
	{
		std::cout << ch << std::endl;
	}

	std::vector<int> input{ 2, 15, 11, 7 };
	const auto& res = LeetTwoSum2(input, 9);
	BOOST_FOREACH(const auto& index, res)
	{
		std::cout << index << std::endl;
	}

	std::cout << LeetReverseInt(-534236469) << std::endl;
	std::cout << LeetAtoi("5342364") << std::endl;
	std::cout << LeetLongestSubstring("calculus") << std::endl;
	std::cout << LeetLongestSubstring("abcabcbb") << std::endl;
	std::cout << LeetLongestSubstring("pwwkew") << std::endl;
	std::cout << LeetLongestSubstring("bbbbb") << std::endl;
	std::vector<int> in2{ -1, 0, 1, 2, -1, -4 };
	std::vector<int> in{ 0, 0, 0, 0 };
	LeetThreeSum2(in);**/

	/**ProducerConsumer produceconsume{};
	produceconsume();**/

	std::cout << "Cuncurrent threads = " << std::thread::hardware_concurrency() << std::endl;
	/**std::thread produce{ T1::Produce };
	std::thread consume{ T1::Consume };
	produce.join();
	consume.join();**/

	std::vector<int> data{ 1,2,3,4,5,6,7,8,9,10,11 };
	std::cout << "Accummulated value = " << T2::Accumulate(data.begin(), data.end(), 10) << std::endl;

	{
		MyTree<int> myTree;
		auto res = myTree.find(4);
		std::cout << "The result of searching for 4 is " << res << std::endl;
		myTree.insert(10);
		myTree.insert(50);
		myTree.insert(3);
		myTree.insert(-1);
		myTree.insert(100);
		myTree.insert(5);
		myTree.GetNodesPerLevel();

		res = myTree.find(3);
		if (res)
			std::cout << "The result of searching for 3 has a value of " << res->m_data << std::endl;
		myTree.printInOrder();
		std::cout << "Min = " << myTree.findMin() << std::endl;
		std::cout << "Max = " << myTree.findMax() << std::endl;
	}

	CustomStack<int> cust_stack;
	cust_stack.push(1);

	CustomStack<int> cust_stack2{ 1, 2, 3, 4, 5 };
	CustomStack<double> cust_stack3;
	cust_stack3 = cust_stack2;
	dbg("cust_stack3 size", cust_stack3.size());
	CustomStack<int> cust_stack4;
	cust_stack4 = cust_stack2;
	CustomStack<int> cust_stack5{ CustomStack<int> {3, 5, 8} };

	Val<int> my_val(7);
	std::cout << "Type name = " << my_val.getType() << std::endl;

	Val<std::string> my_val2("Oh yeah");
	std::cout << "Type name = " << my_val2.getType() << std::endl;

	int num = 30;
	Val<int*> my_val3(&num);
	std::cout << "Type name = " << my_val3.getType() << std::endl;

	MyStack2<int> my_stack2;
	dbg("size", my_stack2.size());
	dbg("capacity", my_stack2.capacity());
	my_stack2.push(10);
	dbg("size", my_stack2.size());
	dbg("capacity", my_stack2.capacity());
	dbg("top", my_stack2.top());
	my_stack2.pop();
	dbg("size", my_stack2.size());

	printAll(data);
	getType(num);

	char test1[] = { 'a', 'b', 'c', 'd', '\0' };
	reverseFunc(test1);
	std::cout << "Rev = " << test1 << std::endl;
	std::cout << "Unique = " << unique_chars2("abcdefghijka") << std::endl;
	char test3[] = "abccde";
	remove_dupes(test3);
	std::cout << "Unique = " << test3 << std::endl;
	char test4[] = "aabccde";
	remove_dupes3(test4);
	std::cout << "Unique = " << test4 << std::endl;
	std::cout << "Are Anagrams?  " << are_anagrams2("listen", "silent") << std::endl;
	Anagrams(std::vector<std::string>{"algorithm", "god", "logarithm", "dog"});
	//std::cout << "Result  " << myStrCmp("", "abc") << std::endl;
	//std::cout << "Result  " << myStrCmp("abc", "") << std::endl;
	//std::cout << "Result  " << myStrCmp("abcd", "abc") << std::endl;
	//std::cout << "Result  " << myStrCmp("abc", "abcd") << std::endl;
	std::cout << "Result  " << myStrCmp("abc", "abc") << std::endl;
	//std::cout << "Result  " << myStrCmp("abc", "def") << std::endl;
	//std::cout << "Result  " << myStrCmp("def", "abc") << std::endl;
	std::cout << "IsSub =  " << is_substr("boomboomd", "boomboomboomd") << std::endl;
	std::cout << "Height = " << UtopianTree(4) << std::endl;

	{
		MyList<int> my_list;
		std::cout << "Size =  " << my_list.size() << std::endl;
		my_list.add(1);
		std::cout << "Size =  " << my_list.size() << std::endl;
		my_list.add(3);
		std::cout << "Size =  " << my_list.size() << std::endl;
		my_list.add(1, 2);
		my_list.addFirst(0);
		std::cout << "Size =  " << my_list.size() << std::endl;
		my_list.print();
		my_list.remove(static_cast<size_t>(0));
		std::cout << "Size =  " << my_list.size() << std::endl;
		my_list.print();
		my_list.remove(2);
		std::cout << "Size =  " << my_list.size() << std::endl;
		my_list.print();
		my_list.clear();
		my_list.add(1);
		my_list.add(2);
		my_list.add(3);
		my_list.add(4);
		my_list.print();
		std::cout << "Reversing List" << std::endl;
		my_list.reverse();
		my_list.print();
	}
	const std::shared_ptr<int> int_ptr = std::make_shared<int>(5);
	const std::shared_ptr<int> int_ptr2 = std::make_shared<int>(5);
	*int_ptr = 7;
	const std::shared_ptr<const int> int_constptr = std::make_shared<int>(5);
	std::cout << "myAtoi =  " << myAtoi("2147483648") << std::endl;
	std::cout << "atoi =  " << atoi("2147483648") << std::endl;

	auto sum = ParrallelAccumulator(data);
	std::cout << "Multi threaded sum = " << sum << std::endl;

	auto lambda = [sum](int acc) {std::cout << "My 1st Lambda = " << sum + acc << std::endl; };
	lambda(100);
	std::string reversed;
	recursive_reverse("Valentine", reversed);
	std::cout << "reversed = " << reversed << std::endl;
	std::cout << std::make_tuple(3.6, "Val", 7, true) << std::endl;
	/*
	1. std::unique_ptr has a specialisation for array types that overloads the subscript operator.
	2. If a default deleter for std::unique_ptr is required, its type must be specified as a template param. This is different to the shared_ptr.
	3. By specifying an array type as the template param, delete[] will be called
	4. If a non array time is specified, then a default_delete with an array time must be used.
	*/
	std::shared_ptr<int> ptrArray{ new int[5], std::default_delete<int[]>{} };
	std::unique_ptr<int[]> uptrArray{ new int[5] };
	for (auto i : { 0, 1, 2, 3, 4 })
	{
		ptrArray.get()[i] = i;
	}
	for (auto i : { 0, 1, 2, 3, 4 })
	{
		std::cout << ptrArray.get()[i] << std::endl;
	}
	for (auto i : { 0, 1, 2, 3, 4 })
	{
		uptrArray[i] = i;
	}
	for (auto i : { 0, 1, 2, 3, 4 })
	{
		std::cout << "Unique " << uptrArray[i] << std::endl;
	}
	auto minmax = LargestIncreasingSubSequence(std::vector<int>{ 10, 3, 7, 9, 0, 15 });
	std::cout << "min: " << minmax.first << " max: " << minmax.second << std::endl;
	std::cout << "Transformed = " << replaceSpaceWithEncoding("h ueiei  u") << std::endl;

	std::vector<int> numbersToSort{ -4, 7, 0, 2, 5, 9, -5, 300, 5 };
	SelectionSort(numbersToSort.begin(), numbersToSort.end());
	printAll(numbersToSort);

	std::cout << "Bubble sort starts " << std::endl;
	std::vector<int> numbersToSort2{ -4, 7, 0, 2, 5, 9, -5, 300, 5 };
	BubbleSort(numbersToSort2.begin(), numbersToSort2.end());
	printAll(numbersToSort2);

	std::cout << "Insertion sort starts " << std::endl;
	std::vector<int> numbersToSort3{ -4, 7, 0, 2, 5, 9, -5, 300, 5 };
	InsertionSort(numbersToSort3.begin(), numbersToSort3.end());
	printAll(numbersToSort3);

	std::cout << "Partition starts " << std::endl;
	std::vector<int> numbersToPartition{ 7, 2, 1, 6, 8, 5, 3, 4 };
	Partition(numbersToPartition.begin(), numbersToPartition.end());
	printAll(numbersToPartition);

	std::cout << "Quick sort starts " << std::endl;
	std::vector<int> numbersToSort4{ -4, 7, 0, 2, 5, 9, -5, 300, 5 };
	QuickSort(numbersToSort4.begin(), numbersToSort4.end());
	printAll(numbersToSort4);

	for (auto i : { 1, 2, 3, 4, 5, 6, 7 })
		std::cout << "fib" << i << " = " << fib(i) << "\n";
	std::cout << "max sub list " << LeetMaximumSubarraySum(std::vector<int>{ -100, 2, 98, 5, 1, 4 }, 5) << std::endl;
	std::cout << "max sub list " << LeetMaximumSubarraySum(std::vector<int>{ -2, -1, 2, 1}, 1) << std::endl;
	PrintDistinctNumbersWithPairs1(std::vector<int>{ 1, 2, 3, 2, 1, 4});
	PrintDistinctNumbersWithPairs1(std::vector<int>{ 2, 1, 3, 2});
	std::vector<int> in{ 1, 3, 5, 7 };
	mergeSortedArrays(in, std::vector<int>{1, 3, 5, 7});
	printAll(in);

	std::cout << "Has element 301 ? " << bin_search_recurse(numbersToSort4.begin(), numbersToSort4.end(), 301) << std::endl;
	std::cout << "Has element 300 ? " << bin_search_recurse(numbersToSort4.begin(), numbersToSort4.end(), 300) << std::endl;
	std::cout << MergeStrings(std::vector<std::string>{"valentine", "oradiegwu"}) << std::endl;
	//std::cout << "Minimum value for int: " << std::numeric_limits<int>::max() << '\n';
	std::vector<int> out{};
	std::vector<int> one{ 0, 2, 3, 4 };
	std::vector<int> two{ 1, 2, 3, 5, 6 };
	intersectTwoSortedRanges(one.begin(), one.end(), two.begin(), two.end(), std::back_inserter(out));
	printAll(out);

	auto twoSum = twoSumSortedAllMatches(std::vector<int>{1, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9}, 8);
	for (auto& item : twoSum)
		std::cout << item.first << ":" << item.second << std::endl;

	std::shared_ptr<int> aPtr1{};
	std::cout << "Use count aPtr1 = " << aPtr1.use_count() << std::endl;
	std::shared_ptr<int> aPtr2{ aPtr1 };
	std::cout << "Use count aPtr1 = " << aPtr1.use_count() << std::endl;
	std::shared_ptr<int> bPtr1{ static_cast<int*>(0) };
	std::cout << "Use count bPtr1 = " << bPtr1.use_count() << std::endl;
	std::shared_ptr<int> bPtr2{ bPtr1 };
	std::cout << "Use count bPtr1 = " << bPtr1.use_count() << std::endl;
	std::shared_ptr<int> cPtr1{ nullptr };
	std::cout << "Use count cPtr1 = " << cPtr1.use_count() << std::endl;
	std::shared_ptr<int> cPtr2{ cPtr1 };
	std::cout << "Use count cPtr1 = " << cPtr1.use_count() << std::endl;
	std::vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	std::cout << "res = " << ParallelAccumulate(input, 0) << std::endl;
	ThreadSafeList<int> stack{};
	FindMaxLengthValidParenthesis("()()()(((()");
	std::cout << FindLargestIncreasingSubSequence(std::vector<int>{1, 2, 3, 2, 4, 6, 8}) << std::endl;
	std::cout << "Is balanced = " << is_balanced_can_contain_nonbraces("jfkfkfk}ui") << std::endl;
	std::cout << "Is balanced = " << is_balanced_can_contain_nonbraces("ryriir{uri[fjjfk]rir}") << std::endl;
	std::cout << "Is balanced = " << is_balanced_can_contain_nonbraces("jfkfkfkui") << std::endl;

	squareRoot2(17);
	std::cout << "First Occurence in bin search = " << binSearchFirstOccurence(std::vector<int>{-5, 1, 1, 1, 1, 6, 8, 9}, 1) << std::endl;
	std::cout << "First Occurence in bin search = " << binSearchFirstOccurence(std::vector<int>{-5, 1, 1, 1, 1, 6, 8, 9}, 10) << std::endl;
	std::cout << "First Occurence in bin search = " << binSearchFirstOccurence(std::vector<int>{-5, 1, 1, 1, 1, 6, 8, 9}, -6) << std::endl;
	std::cout << "First Occurence in bin search = " << binSearchFirstOccurence(std::vector<int>{1, 1, 1, 1, 6, 8, 9}, 1) << std::endl;
	std::cout << "Number of occurences = " << searchNumOccurrenceR(std::vector<int>{1, 2, 3, 3, 3, 4, 5, 8}, 3, 0, 7) << std::endl;

	std::cout << "Number of set bits = " << CountBitsInInt(7) << std::endl;
	std::cout << "Multiply = " << multiplyStrings("999", "999") << std::endl;

	auto rot1 = rotateArray(std::vector<int>{1, 2, 3, 4, 5}, 1);
	auto rot2 = rotateArray(std::vector<int>{1, 2, 3, 4, 5}, 5);

	//findSchedules(56, 8, "???8???");
	findSchedules(24, 4, "08??840");
	const char bla[] = { "Val" };
	auto change = coinChange(std::vector<int>{ 25, 10, 5 }, 30);
	std::vector<int> testNumber{ 9, 9, 9 };
	addOneToVector(testNumber);

	std::vector<int> testNumber1{ 9, 9, 8 };
	addOneToVector(testNumber1);
	mergeInterval(std::vector<std::pair<int, int>>{ {6, 8}, { 1,9 }, { 2,4 }, { 4,7 } });
	//insertAndMergeInterval(std::vector<std::pair<int, int>>{ {1, 3}, { 6,9 } }, {2, 5});
	//insertAndMergeInterval(std::vector<std::pair<int, int>>{ {1, 2}, { 3,5 }, { 6,7 }, { 8,10 }, { 12,16 } }, { 4, 9 });
	//insertAndMergeInterval(std::vector<std::pair<int, int>>{ {4, 5}, { 6, 9 } }, { 2, 3 });
	insertAndMergeInterval2(std::vector<std::pair<int, int>>{ {4, 5}, { 6, 15 } }, { 10, 13 });
	repeatedNumberModify(std::vector<int>{ 3, 4, 1, 4, 1});
	findSingleNumber(std::vector<int>{ 7, 3, 5, 4, 5, 3, 4 });

	HierarchicalObject granddad{ nullptr, {"Mbadike", "Oradiegwu"} };
	HierarchicalObject dad{ &granddad,{ "Nwabike", "Oradiegwu" } };
	HierarchicalObject son{ &dad,{ "Obiajulu", "Oradiegwu" } };
	son.merge_names();
	son.print();

	auto len = my_mem_fn(&std::string::size);
	//auto len = std::mem_fn(&std::string::size);
	std::cout << len(std::string{ "Val" }) << '\n';
	//auto some_string{"Val"};
	//std::cout << len(&some_string) << '\n';
	VendingMachine vm{};
	vm.Start();

	auto server = std::thread{ Rep_Server{} };
	auto client = std::thread{ Rep_Client{} };
	server.detach();
	client.join();
	{
		std::vector<std::future<int>> futures{};
		ThreadPool<int()> pool{};
		for (auto i : { 1, 3, 4, 7 })
		{
			std::packaged_task<int()> job{ std::bind(&Factorial, i) };
			futures.push_back(job.get_future());
			pool.push(job);
		}
		for (auto& future : futures)
			std::cout << "Factorial = " << future.get() << std::endl;
	}
	Any_Callable<int(int)> any_callable{ &Factorial };
	std::cout << "Factorial on my callable = " << any_callable(7) << std::endl;
	std::cout << "Equivalent = " << checkEquivalentKeypresses("a,b,c,c,-B,d", "a,b,c,d") << std::endl;
	std::cout << "Equivalent = " << checkEquivalentKeypresses("-B,-B,-B,c,c", "c,c") << std::endl;
	std::cout << "Equivalent = " << checkEquivalentKeypresses("", "a,-B,-B,a,-B,a,b,c,c,c,d") << std::endl;

	system("PAUSE");
	return 0;
}