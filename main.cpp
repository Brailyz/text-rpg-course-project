#include "Character.hpp"
#include "Item.hpp"

#include <iostream>
#include <memory>
#include <utility>

int main()
{
	// Композиция и агрегация + shared_ptr
	std::cout << "AGGREGATION + COMPOSITION\n\n";

	auto potion = std::make_shared<Item>("Healing potion", "Restores health");
	std::cout << "potion use_count: " << potion.use_count() << "\n";

	{
		Character character("Arthur", 100, 100);
		character.ShowInfo();

		std::cout << "\nAdd item:\n";
		character.AddItem(potion);
		std::cout << "potion use_count: " << potion.use_count() << "\n";

		std::cout << "\nInventory:\n";
		character.ShowInventory();

		std::cout << "\nUse item:\n";
		character.UseItem(potion);

		std::cout << "\nAdd the same item again:\n";
		character.AddItem(potion);

		std::cout << "\nDeal negative damage:\n";
		character.TakeDamage(-10);

		std::cout << "\nDeal correct damage:\n";
		character.TakeDamage(25);
		character.ShowInfo();

		std::cout << "\nExit the block. Character and Inventory will be destroyed.\n";
	}

	std::cout << "\npotion use_count after the block: " << potion.use_count() << "\n";
	std::cout << "The potion is still alive:\n";
	potion->ShowInfo();

	// Статический объект
	std::cout << "\n\nSTATIC OBJECT\n\n";

	Item staticItem("Sword", "Metal sword");
	staticItem.ShowInfo();

	// unique_ptr
	std::cout << "\n\nUNIQUE_PTR DYNAMIC OBJECT\n\n";

	{
		auto bow = std::make_unique<Item>("Bow", "Wooden bow");

		bow->ShowInfo();
		(*bow).Use();

		Item& bowRef = *bow;
		bowRef.Use();

		std::cout << "\nExit the block. No delete is needed:\n";
	}

	std::cout << "\n\nUNIQUE_PTR MOVE OWNERSHIP\n\n";

	auto crossbow = std::make_unique<Item>("Crossbow", "Heavy crossbow");
	std::cout << "crossbow is empty before move: " << (crossbow == nullptr) << "\n";

	auto newOwner = std::move(crossbow);

	std::cout << "crossbow is empty after move: " << (crossbow == nullptr) << "\n";
	std::cout << "newOwner is empty after move: " << (newOwner == nullptr) << "\n";
	newOwner->ShowInfo();

	// Динамический массив объектов
	std::cout << "\n\nDYNAMIC ARRAY OF OBJECTS\n\n";

	{
		auto itemArray = std::make_unique<Item[]>(2);

		itemArray[0].Set("Shield", "Protects from attacks");
		itemArray[1].Set("Helmet", "Protects head");

		itemArray[0].ShowInfo();
		itemArray[1].ShowInfo();

		std::cout << "\nExit the block:\n";
	}

	// Массив динамических объектов
	std::cout << "\n\nARRAY OF DYNAMIC OBJECTS\n\n";

	{
		std::unique_ptr<Item> itemPointers[2]{};

		itemPointers[0] = std::make_unique<Item>("Ring", "Magic ring");
		itemPointers[1] = std::make_unique<Item>("Amulet", "Protective amulet");

		itemPointers[0]->ShowInfo();
		itemPointers[1]->ShowInfo();

		std::cout << "\nExit the block:\n";
	}

	// shared_ptr
	std::cout << "\n\nSHARED_PTR: use_count\n\n";

	auto shared1 = std::make_shared<Item>("Staff", "Wizard staff");
	std::cout << "use_count: " << shared1.use_count() << "\n";

	{
		auto shared2 = shared1;
		std::cout << "after copy, use_count: " << shared1.use_count() << "\n";

		{
			auto shared3 = shared1;
			std::cout << "after second copy, use_count: " << shared1.use_count() << "\n";
		}

		std::cout << "after a copy is destroyed, use_count: " << shared1.use_count() << "\n";
	}

	std::cout << "after another copy is destroyed, use_count: " << shared1.use_count() << "\n";

	std::cout << "\nReset the last owner:\n";
	shared1.reset();

	// weak_ptr
	std::cout << "\n\nWEAK_PTR\n\n";

	{
		auto ring = std::make_shared<Item>("Ring of power", "Ancient ring");
		std::weak_ptr<Item> observer = ring;

		std::cout << "weak_ptr does not increase use_count: " << ring.use_count() << "\n";

		if (const auto locked = observer.lock())
		{
			std::cout << "lock() succeeded, use_count: " << locked.use_count() << "\n";
			locked->ShowInfo();
		}

		Character mage("Merlin", 80, 100);
		mage.AddItem(ring);
		mage.UseItem(ring);
		mage.ShowLastUsedItem();

		std::cout << "\nRemove the item from the inventory and release the last owner:\n";
		mage.RemoveItem(ring.get());
		ring.reset();

		if (const auto locked = observer.lock())
		{
			locked->ShowInfo();
		}
		else
		{
			std::cout << "the object is gone\n";
		}

		mage.ShowLastUsedItem();

		std::cout << "\nExit the block:\n";
	}

	return 0;
}