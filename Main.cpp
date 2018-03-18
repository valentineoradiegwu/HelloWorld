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
#include <thread>
#include "mytemplates.h"

void hello()
{
	std::cout << "Hello Concurrent World\n";
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

	/*{
		typedef Node<int>* NodeIntPtr;
		MyTree<int> myTree;
		NodeIntPtr res = myTree.find(4);
		std::cout << "The result of searching for 4 is " << res << std::endl;
		myTree.insert(10);
		myTree.insert(50);
		myTree.insert(3);
		myTree.insert(-1);
		myTree.insert(100);
		myTree.insert(5);

		res = myTree.find(3);
		if (res)
		{
			std::cout << "The result of searching for 3 has a value of " << res->m_data << std::endl;
		}
		myTree.printInOrder();
	}*/
	MyStack<int> my_stack;
	my_stack.push(1);

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
	std::cout << "Are Anagrams?  " << are_anagrams("listen", "silent") << std::endl;
	//std::cout << "Result  " << myStrCmp("", "abc") << std::endl;
	//std::cout << "Result  " << myStrCmp("abc", "") << std::endl;
	//std::cout << "Result  " << myStrCmp("abcd", "abc") << std::endl;
	//std::cout << "Result  " << myStrCmp("abc", "abcd") << std::endl;
	std::cout << "Result  " << myStrCmp("abc", "abc") << std::endl;
	//std::cout << "Result  " << myStrCmp("abc", "def") << std::endl;
	//std::cout << "Result  " << myStrCmp("def", "abc") << std::endl;
	std::cout << "IsSub =  " << is_substr("vale", "valfvalg") << std::endl;
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
	system("PAUSE");
	return 0;
}