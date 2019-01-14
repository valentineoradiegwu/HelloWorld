#pragma once
#include <iostream>
#include<tuple>

//Partial specialization of functions is not allowed.
//We will need wrap up in a class.

template <int IDX, int MAX, typename... Types>
struct PRINT_TUPLE
{
	static void print(std::ostream& os, const std::tuple<Types...>& input)
	{
		os << std::get<IDX>(input) << (IDX + 1 == MAX ? "" : ",");
		PRINT_TUPLE<IDX + 1, MAX, Types...>::print(os, input);
	}
};

template <int MAX, typename... Types>
struct PRINT_TUPLE<MAX, MAX, Types...>
{
	static void print(std::ostream& os, const std::tuple<Types...>& input)
	{
	}
};

template <typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& input)
{
	os << "[";
	PRINT_TUPLE<0, sizeof...(Types), Types...>::print(os, input);
	os << "]";
	return os;
}