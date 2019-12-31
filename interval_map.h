#pragma once
#include <map>
#include <limits>

template <typename K, typename V>
class interval_map
{
	std::map<K, V> m_map;
public:
	interval_map(const V& init);
	const V& operator[](const K& idx) const;
	void print() const;
	void clear();
	void assign(const K& keyBegin, const K& keyEnd, const V& val);
};

template <typename K, typename V>
interval_map<K, V>::interval_map(const V& init)
	:m_map{}
{
	m_map[std::numeric_limits<K>::min()] = init;
}

template <typename K, typename V>
void interval_map<K, V>::clear()
{
	m_map.clear();
}

template <typename K, typename V>
void interval_map<K, V>::operator[](const K& idx) const
{
	auto upper = m_map.upper_bound(idx);
	return (--upper)->second;
}

template <typename K, typename V>
void interval_map<K, V>::print() const
{
	
}

/* 
	Assign value val to interval [keyBegin, keyEnd).
	Overwrite previous values in this interval.
	Conforming to the C++ Standard Library conventions, the interval
	includes keyBegin, but excludes keyEnd.
	If !( keyBegin < keyEnd ), this designates an empty interval,
	and assign must do nothing.
*/
template <typename K, typename V>
void assign(const K& keyBegin, const K& keyEnd, const V& val)
{
	/*
	1. We insert an interval at the end. In which case KeyBegin > current max
	2. We insert an interval completely within an existing interval. How to u establish this?
		a. do upper_bound on KeyStart.
		b. subtract 1 from the result to get lower bound.
		c. Scenario is satisfied if upper_bound > KeyEnd and lower bound is < KeyBegin
	3. We insert an interval that overlaps on left or right or completely subsumes another.
	*/

	if !(keyBegin < keyEnd)
		return;

	auto right = m_map.upper_bound(keyBegin);
	if (right == m_map.end())
	{
		// Scenario 1 applies and this new range will be at the end of the map.
		auto currentLast = right - 1;
		if (currentLast->second == val)
			return;

		m_map[KeyBegin] = val;
		m_map.emplace_hint(m_map.end(), keyEnd, currentLast->second);
		return;
	}

	if (right->first > KeyEnd && (right - 1)->first < KeyBegin)
	{
		//Scenario 2 applies since interval is within existing one
		m_map[KeyBegin] = val;
		m_map[KeyEnd] = right->second;
		return;
	}

	// Various variant of scenario 3 with overlaps
	auto left = m_map.upper_bound(keyEnd);
	auto front = m_map.emplace(keyBegin, val);

	if (!front->second)
		front->first->second = val;

	auto valAtEnd = (left - 1)->first;
	auto back = m_map.emplace(keyEnd, valAtEnd);

	if (!back->second)
		back->first->second = valAtEnd;

	auto start = front->first + 1;
	while (start < back)
	{
		auto temp = start;
		++start;
		m_map.erase(temp);
	}
}