#pragma once
/*
1. Default ctor
2. Copy ctor
3. Copy ctor member template
4. assignment
5. Assignment member template
6. ==
7. !=
8. operator*
9. operator!
10.operator->
11. get member function
12. Dtor which will check use count
13. use_count
14. reset
15. reset member template
16. meber function that decreases count and possibly calls delete on the owned ptr
17. Don't forget the move analogues
*/
namespace val
{

	struct Rep
	{
		Rep(size_t usecount = 0)
			:m_usecount{ usecount }
		{}
		size_t m_usecount;
	};

	template <typename T>
	class shared_ptr
	{
		Rep* m_rep;
		T* m_owned;
	public:
		shared_ptr();
		shared_ptr(const shared_ptr& rhs);
		shared_ptr(shared_ptr&& rhs);
		shared_ptr& operator=(shared_ptr rhs);
		T& operator*() const { return *m_owned; }
		T* operator->() const { return get(); }

		template <typename T2>
		shared_ptr(const shared_ptr& rhs);

		/*template <typename T2>
		shared_ptr(shared_ptr&& rhs);*/

		T* get() const { return m_owned; }
		size_t use_count() const { return m_rep ? m_rep->m_usecount : 0; }

		~shared_ptr();

	};

	template <typename T>
	shared_ptr<T>::shared_ptr()
		:m_rep{ new Rep{0} },
		m_owned{nullptr}
	{}

	template <typename T>
	shared_ptr<T>::~shared_ptr()
	{
		if (m_rep)
		{
			//Handles the case where we create an empty shared_ptr with no target
			//Programming error yes but u gotta handle it.
			if (m_rep->m_usecount == 0)
			{
				delete m_owned;
				delete m_rep;
				return;
			}

			if (--m_rep->m_usecount == 0)
			{
				delete m_owned;
				delete m_rep;
			}
		}
	}

	template <typename T>
	shared_ptr<T>::shared_ptr(const shared_ptr& rhs)
		:m_rep{ rhs.m_rep },
		m_owned{ rhs.m_owned }
	{
		++m_rep->m_usecount;
	}

	template <typename T>
	template <typename T2>
	shared_ptr<T>::shared_ptr(const shared_ptr<T2>& rhs)
		:m_rep{ rhs.m_rep }
	{
		m_owned = rhs.get();
		++m_rep->m_usecount;
	}

	template <typename T>
	shared_ptr<T>::shared_ptr(shared_ptr&& rhs)
		:m_rep{ rhs.m_rep },
		m_owned{ rhs.m_owned }
	{
		rhs.m_rep == nullptr;
		rhs.m_owned == nullptr;
	}

	template <typename T>
	shared_ptr<T>::shared_ptr& shared_ptr<T>::operator=(shared_ptr rhs)
	{
		//Copy and swap idiom
		std::swap(m_rep, rhs.m_rep);
		std::swap(m_owned, rhs.m_owned);
	}

	/*template <typename T>
	template <typename T2>
	shared_ptr<T>::shared_ptr(shared_ptr<T2>&& rhs)
		:m_rep{ rhs.m_rep },
		m_owned{ rhs.get() }
	{
		//Need to create a get which returns a ref here
		rhs.m_rep == nullptr;
		rhs.m_owned == nullptr;
	}*/

	//How do u think the default delete class is defined?
	template <typename T>
	struct default_delete
	{
		void operator(T* owned) const
		{
			delete owned;
		}
	};

	template <typename T>
	struct default_delete<T[]>
	{
		void operator(T* owned) const
		{
			delete[] owned;
		}
	};
}
