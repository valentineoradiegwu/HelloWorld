#pragma once
template <typename T1, typename T2>
struct MyPair
{
	using first_type = T1;
	using second_type = T2;
	MyPair();

	template <typename U1=T1, typename U2=T2>
	MyPair(const U1& val1, const U2& val2);
	MyPair(const MyPair&) = default;
	MyPair(MyPair&&) = default;
	MyPair(T1&& val1, T2&& val2);
	T1 first;
	T2 second;
};

template <typename T1, typename T2>
MyPair<T1, T2>::MyPair()
	:first{},
	second{}
{}

template <typename T1, typename T2>
template <typename U1, typename U2>
MyPair<T1, T2>::MyPair(const U1& val1, const U2& val2)
	:first{val1},
	second{val2}
{}

template <typename T1, typename T2>
MyPair<T1, T2>::MyPair(T1&& val1, T2&& val2)
	:first{val1},
	second{val2}
{}
