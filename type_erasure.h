#pragma once
#include <memory>

/*
Duck typing is an interesting feature provided by some programming languages such as golang.
An interface provides a public contract and any type which has the same contract can be assigned
to a variable of this interface. This also makes it way to C++ where variables of std::function can
be assigned any variable that overrides the function call operaror. We will try to implement a 
callable like std::function. https://www.modernescpp.com/index.php/c-core-guidelines-type-erasure-with-templates
*/

template<typename>
class Any_Callable;

template <typename Ret, typename... Args>
class Any_Callable<Ret(Args...)>
{
public:
	template <typename Callable>
	Any_Callable(const Callable& rhs)
		:target{ std::make_shared<Model<Callable>>(rhs) }
	{}

	template <typename Callable>
	Any_Callable(Callable&& rhs)
		: target{ std::make_shared<Model<Callable>>(std::move(rhs)) }
	{}

	Ret operator()(const Args &... args) const
	{
		return (*target)(args...);
	}

	template <typename Callable>
	Any_Callable& operator=(const Callable& rhs)
	{
		target.reset(std::make_shared<Model<Callable>>(rhs));
	}

	template <typename Callable>
	Any_Callable& operator=(Callable&& rhs)
	{
		target.reset(std::make_shared<Model<Callable>>(std::move(rhs)));
	}
private:
	struct Concept
	{
		virtual Ret operator()(const Args &... args) const = 0;
		virtual ~Concept() {}
	};
	template <typename T>
	struct Model : Concept
	{
		Model(const T& functor)
			:m_callable{ functor }
		{}
		Model(T&& functor)
			:m_callable{ std::move(functor) }
		{}
		virtual Ret operator()(const Args&... args) const override
		{
			return m_callable(args...);
		}
		T m_callable;
	};
	std::shared_ptr<Concept> target;
};
