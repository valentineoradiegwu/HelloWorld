#pragma once
#include <unordered_map>
#include <list>
#include <stdexcept>
#include <thread>

template <typename K, typename V>
class LRUCache
{
public:
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
	using ListType = std::list<Node>;
	using MapType = std::unordered_map<const K, decltype(m_list.begin())>;

private:
	MapType m_cache;
	ListType m_list;
	size_t m_maxsize;
	std::mutex m_lock;
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
	std::lock_guard<std::mutex>{m_lock};
	auto item = m_cache.find(key);
	if (item == m_cache.end())
	{
		throw std::invalid_argument{ "Key does not exist in cache" };
	}
	else
	{
		m_list.splice(m_list.begin(), m_list, item->second);
		return item->second->m_value;
	}
}

template <typename K, typename V>
void LRUCache<K, V>::put(const K& key, const V& value)
{
	std::lock_guard<std::mutex>{m_lock};
	if (m_cache.size() > m_maxsize)
	{
		auto key = m_list.back().m_key;
		m_list.pop_back();
		m_cache.erase(key);
	}

	auto item = m_cache.find(key);
	if (item == m_cache.end())
	{
		m_list.push_front(Node{key, value});
		m_cache.insert(MapType::value_type{ key, m_list.begin() });
	}
	else
	{
		//Updates the existing. Can throw if the value cant be updated
		item->second->m_value = value;
	}
}

template <typename K, typename V>
void LRUCache<K, V>::erase(const K& key)
{
	std::lock_guard<std::mutex>{m_lock};
	auto item = m_cache.find(key);
	if (item != m_cache.end())
	{
		m_list.erase(item->second);
		m_cache.erase(item);
	}
}