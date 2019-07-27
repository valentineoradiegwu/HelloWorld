#pragma once
#include <utility>
//We would be creating a functor and a utility function which makes this functor.

//1. Needs a funtion operator.
//2. Needs a member to store the member function pointer with the general type R (T::*)()
template <typename MemFn>
class my_mem_fn_t
{
	MemFn m_pmf;
public:
	my_mem_fn_t(MemFn pmf )
		:m_pmf{pmf}
	{}

	template <typename T>
	decltype(auto) operator()(T&& t) const
	{
		return (std::forward<T>(t).*m_pmf)();
	}
};

template <typename Result, typename T>
decltype(auto) my_mem_fn(Result T::* pmf)
{
	return my_mem_fn_t<Result T::*>{pmf};
}


