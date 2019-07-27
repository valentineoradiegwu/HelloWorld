#pragma once
#include <unordered_map>
#include <string>
class VendingMachine
{
public:
	VendingMachine();
	void Start();
private:
	enum class Item {COKE, FANTA, PEPSI, SPRITE, QUIT, NONE, END};
	enum class State {WELCOME, QUANTITY, PAYMENT, UPDATE, QUIT};
	using InventoryType = std::unordered_map<Item, std::pair<int, const double>>;
	InventoryType m_inventory;
	State m_state;
	bool isItemValid(int item_descriptor) const;
	static InventoryType PopulateInventory();
	static std::string str(Item item);
};
