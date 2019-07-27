#include "vending_machine.h"
#include <iostream>


VendingMachine::VendingMachine()
	:m_inventory{ PopulateInventory()},
	m_state{State::WELCOME}
{}

void VendingMachine::Start()
{
	Item selection = Item::NONE;
	int quantity{};
	while (true)
	{
		switch (m_state)
		{
		case State::WELCOME:
			{
				std::cout << "Welcome to Valentine's Vending machine. We have the following items below;" << std::endl;
				for (const auto& inventory_item : m_inventory)
				{
					std::cout << inventory_item.second.first << " " << str(inventory_item.first) << 
					" costing " << char(156) << inventory_item.second.second << ". Enter " <<
					static_cast<int>(inventory_item.first) << " to select it or " << static_cast<int>(Item::QUIT) << " to QUIT." << std::endl;
				}
				
				int select;
				std::cin >> select;
				if (isItemValid(select))
				{
					selection = static_cast<Item>(select);
					if(selection == Item::QUIT)
						m_state = State::QUIT;
					else
						m_state = State::QUANTITY;
				}
				else
				{
					std::cout << "You have entered an invalid item " << select << std::endl;
				}
				break;
			}
		case State::QUANTITY:
			{
				std::cout << "How many " << str(selection) << " would you like? " << std::endl;
				std::cin >> quantity;
				auto inventory_quantity = m_inventory[selection].first;
				if (quantity > inventory_quantity)
				{
					std::cout << "We only have " << inventory_quantity << " left. Please amend specified quantity " << std::endl;
				}
				else
				{
					m_state = State::PAYMENT;
				}
				break;
			}
		case State::PAYMENT:
			{
				std::cout << "Make your payment " << std::endl;
				double payment;
				std::cin >> payment;
				auto cost = quantity * m_inventory[selection].second;
				if (payment < cost)
				{
					std::cout << quantity << " " << str(selection) <<  " at " << char(156) <<  m_inventory[selection].second << " costs " << cost << ". Add more money." << std::endl;
				}
				else
				{
					m_inventory[selection].first = m_inventory[selection].first - quantity;
					m_state = State::WELCOME;
				}
				break;
			}
		case State::QUIT: return;
		}
	}
}

VendingMachine::InventoryType VendingMachine::PopulateInventory()
{
	VendingMachine::InventoryType inv = { { Item::COKE, { 10, 1 } },
	                                      { Item::FANTA, { 18, 1.5 } },
										  { Item::PEPSI, { 15, 1.2 } },
										  { Item::SPRITE, { 3, 1.3 } }
	                                    };
	return inv;
}

bool VendingMachine::isItemValid(int item_descriptor) const
{
	return item_descriptor >= 0 && item_descriptor < static_cast<int>(Item::END);
}

std::string VendingMachine::str(Item item)
{
	std::string item_string{};
	switch (item)
	{
	case Item::COKE: item_string = "COKE"; break;
	case Item::FANTA: item_string = "FANTA"; break;
	case Item::PEPSI: item_string = "PEPSI"; break;
	case Item::SPRITE: item_string = "SPRITE"; break;
	}
	return item_string;
}