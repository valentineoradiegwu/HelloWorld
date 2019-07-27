#include <iostream>
#include "HierarchicalObject.h"

HierarchicalObject::HierarchicalObject(HierarchicalObject* parent, std::initializer_list<std::string> names)
	:m_parent{parent},
	m_names(names.begin(), names.end())
{}

void HierarchicalObject::merge_names()
{
	if (m_parent)
	{
		m_parent->merge_names();
		for (const auto& name : m_parent->m_names)
			m_names.push_back(name);
	}
}

void HierarchicalObject::print() const
{
	std::cout << "[";
	std::string del{ "" };
	for (const auto& name : m_names)
	{
		std::cout << del << name;
		del = ", ";
	}
	std::cout << "]" << std::endl;
}