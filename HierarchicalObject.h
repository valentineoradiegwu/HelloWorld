#pragma once
#include <vector>
#include <string>
#include<initializer_list>

struct HierarchicalObject
{
	HierarchicalObject(HierarchicalObject* parent, std::initializer_list<std::string> names);
	HierarchicalObject* const m_parent;
	std::vector<std::string> m_names;
	void merge_names();
	void print() const;
};
