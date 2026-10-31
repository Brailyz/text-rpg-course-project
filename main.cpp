#include "Character.hpp"
#include "Item.hpp"

#include <iostream>

int	main() {
	
	// Агрегация
	std::cout << "AGREGATION\n\n";

	Item potion("Healing potion", "Healing potion. Restores health");

	{
		Character character("Arthur", 100, 100);

		character.ShowInfo();

		// Добавление предмета
		std::cout << "\nAdd item:\n";
		character.AddItem(&potion);

		// Состояние инвентаря
		std::cout << "\nInventory:\n";
		character.ShowInventory();

		// Использовать предмет
		std::cout << "\nUse item:\n";
		character.UseItem(&potion);

		// Нанесение отрицательного урона
		std::cout << "\nDeal negative damage:\n";
		character.TakeDamage(-10);

		// Корректный урон
		std::cout << "\nDeal correct damage:\n";
		character.TakeDamage(25);

		character.ShowInfo();

		std::cout << "\nExit the block. Character and Inventory will be destroyed.\n";
	}

	std::cout << "\n";

	potion.ShowInfo();

	// Статический объект
	std::cout << "\n\nSTATIC OBJECT\n\n";

	Item sword("Sword", "Metal sword");
	sword.ShowInfo();

	// Динамический объект
	std::cout << "\n\nDYNAMIC OBJECT\n\n";

	auto* dynamicItem = new Item("Bow", "Wooden bow");

	dynamicItem->ShowInfo();
	(*dynamicItem).Use();
	dynamicItem->Use();

	delete dynamicItem;

	// Динамический массив объектов

	std::cout << "\n\nDYNAMIC ARRAY OF OBJECTS\n\n";

	auto* itemArray = new Item[2]{
		{ "Shield", "Protects from attacks" },
		{ "Helmet", "Protects head" }
	};

	itemArray[0].ShowInfo();
	itemArray[1].ShowInfo();

	delete[] itemArray;

	// Массив динамических объектов

	std::cout << "\n\nARRAY OF DYNAMIC OBJECTS\n\n";

	Item* itemPointers[2]{};

	itemPointers[0] = new Item( "Ring", "Magic ring" );
	itemPointers[1] = new Item{ "Amulet", "Protective amulet" };

	itemPointers[0]->ShowInfo();
	itemPointers[1]->ShowInfo();

	delete itemPointers[0];
	delete itemPointers[1];

	return	0;
}
