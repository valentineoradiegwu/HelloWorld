#pragma once
#include <unordered_map>
#include <list>
#include <stdexcept>

template <typename K, typename V>
class LRUCache
{
public:
	template <typename K, typename V>
	struct Node
	{
		Node(K key, V value)
			:m_key{ key },
			m_value{ value }
		{}
		K m_key;
		V m_value;
	};
	LRUCache(size_t size = 20);
	void put(const K& key, const V& value);
	K get(const K& key);
	void erase(const K& key);
	using ListType = std::list<Node<K, V>>;
	using MapType = std::unordered_map<const K, decltype(m_list.begin())>;

private:
	MapType m_cache;
	ListType m_list;
	size_t m_maxsize;
};

template <typename K, typename V>
LRUCache<K, V>::LRUCache(size_t size)
	:m_cache{},
	m_list{},
	m_maxsize{ size }
{}

template <typename K, typename V>
K LRUCache<K, V>::get(const K& key)
{
	auto item = m_cache.find(key);
	if (item == m_cache.end())
	{
		throw std::invalid_argument{ "Key does not exist in cache" };
	}
	else
	{
		auto key = item->second->m_key;
		auto value = item->second->m_value;

		m_list.erase(item->second);
		m_cache.erase(item);

		m_list.push_front(Node<K, V>{key, value});
		m_cache.insert(MapType::value_type{ key, m_list.begin() });

		return value;
	}
}

template <typename K, typename V>
void LRUCache<K, V>::put(const K& key, const V& value)
{
	if (m_cache.size() > m_maxsize)
	{
		auto key = m_list.back().m_key;
		m_list.pop_back();
		m_cache.erase(key);
	}

	auto item = m_cache.find(key);
	if (item == m_cache.end())
	{
		m_list.push_front(Node<K, V>{key, value});
		m_cache.insert(MapType::value_type{ key, m_list.begin() });
	}
	else
	{
		auto key = item->second->m_key;
		auto value = item->second->m_value;

		m_list.erase(item->second);
		m_cache.erase(item);

		m_list.push_front(Node<K, V>{key, value});
		m_cache.insert(MapType::value_type{ key, m_list.begin() });
	}
}

template <typename K, typename V>
void LRUCache<K, V>::erase(const K& key)
{
	auto item = m_cache.find(key);
	if (item != m_cache.end())
	{
		m_list.erase(item->second);
		m_cache.erase(item);
	}
}