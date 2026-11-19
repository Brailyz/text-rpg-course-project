#include "Character.hpp"
#include "Potion.hpp"
#include "Weapon.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace
{
    void PrintSection(const std::string& title)
    {
        std::cout << "\n===== " << title << " =====\n";
    }

    void DemoConstructors()
    {
        PrintSection("1. Constructors: default, parameterized, copy, move");

        Weapon defaultWeapon;
        Weapon sword{ "Sword", "Sharp steel blade with a runic edge", 15, ItemEffect{ "Fire", 5 } };
        Weapon swordCopy{ sword };
        Weapon swordMoved{ std::move(swordCopy) };

        std::cout << "--- end of scope: destructors run in reverse order ---\n";
    }

    void DemoDeepCopy()
    {
        PrintSection("2. Deep copy: copy constructor and Clone()");

        Weapon original{ "Axe", "Heavy two-handed axe", 20, ItemEffect{ "Ice", 4 } };

        Weapon copy{ original };
        copy.SetEffectPower(100);
        std::cout << "Copy changed to 100. Original effect power: " << original.GetEffectPower() << '\n';

        const std::unique_ptr<BaseItem> clone = original.Clone();
        original.SetEffectPower(50);
        std::cout << "Original changed to 50. Original / clone:\n";
        original.Describe();
        clone->Describe();

        std::cout << "--- end of scope ---\n";
    }

    void DemoShallowCopy()
    {
        PrintSection("3. Shallow copy: effect is shared (shared_ptr)");

        Potion elixir{ "Elixir", "Glowing red liquid", 30, ItemEffect{ "Regeneration", 3 } };
        Potion elixirCopy{ elixir };

        elixirCopy.SetEffectPower(77);
        std::cout << "Copy changed to 77, original sees it too:\n";
        elixir.Describe();
        std::cout << "use_count = " << elixir.GetEffectUseCount() << '\n';

        std::cout << "--- end of scope ---\n";
    }

    void DemoAssignment()
    {
        PrintSection("4. Assignment: self-assignment check, return *this");

        Weapon a{ "Dagger", "Small and quick", 8, ItemEffect{ "Poison", 2 } };
        Weapon b;
        Weapon c{ "Spear", "Long reach", 12, ItemEffect{ "Wind", 1 } };

        b = a;
        Weapon& alias = a;

        // самоприсваивание
        a = alias; 
        b = std::move(c);

        a.SetDescription("Updated").SetDescription("Updated twice");
        a.Describe();

        std::cout << "--- end of scope ---\n";
    }

    void DemoVirtualDestructor()
    {
        PrintSection("5. Virtual destructor: deleting derived through base pointer");

        {
            std::unique_ptr<BaseItem> item = std::make_unique<Potion>("Mana potion", "Blue and bitter", 10, ItemEffect{ "Focus", 1 });

            std::cout << "--- leaving scope ---\n";
        }

        std::cout << "Both ~Potion and ~BaseItem must have run above.\n";
    }

    void DemoStrings(const BaseItem& first, const BaseItem& second)
    {
        PrintSection("7.1 Strings: concatenation, find, substr, compare");

        std::cout << "Title (concatenation): " << first.GetTitle() << '\n';
        std::cout << "Contains \"runic\" (find): " << std::boolalpha
            << first.DescriptionContains("runic") << '\n';
        std::cout << "Short description (substr): " << first.GetShortDescription(12) << '\n';
        std::cout << "Same name as second (compare): " << first.HasSameName(second) << '\n';
    }

    void DemoPolymorphism()
    {
        PrintSection("7. Array of unique_ptr, work through base pointer");

        std::array<std::unique_ptr<BaseItem>, 3> items{
            std::make_unique<Weapon>("Runic sword", "A sword with a runic edge", 15, ItemEffect{ "Fire", 5 }),
            std::make_unique<Potion>("Healing potion", "Restores health quickly", 25, ItemEffect{ "Heal", 2 }),
            std::make_unique<Weapon>("Bow", "Elven bow", 10, ItemEffect{ "Wind", 3 })
        };

        for (const auto& item : items)
        {
            item->Describe(); 
            item->Use();      
        }

        DemoStrings(*items[0], *items[1]);

        std::cout << "Objects created so far (static counter): " << BaseItem::GetCreatedCount() << '\n';
        std::cout << "--- end of scope: array releases all items ---\n";
    }

    void DemoCharacter()
    {
        PrintSection("8. Character, inventory, shared_ptr / weak_ptr");

        Character hero{ "Hero", 100, 100 };

        std::unique_ptr<BaseItem> uniqueSword = std::make_unique<Weapon>("Hero sword", "Plain but reliable", 14, ItemEffect{ "None", 0 });
        std::shared_ptr<BaseItem> sword = std::move(uniqueSword);

        auto potion = std::make_shared<Potion>("Small potion", "Tastes like berries", 15, ItemEffect{ "Heal", 1 });

        hero.AddItem(sword);
        hero.AddItem(potion);
        hero.AddItem(potion); // повторное добавление

        hero.UseItem(potion);
        hero.ShowLastUsedItem();

        hero.RemoveItem(potion.get());
        potion.reset(); 
        hero.ShowLastUsedItem();
        hero.ShowInventory();

        std::cout << "--- end of scope ---\n";
    }
} 

int main()
{
    DemoConstructors();
    DemoDeepCopy();
    DemoShallowCopy();
    DemoAssignment();
    DemoVirtualDestructor();
    DemoPolymorphism();
    DemoCharacter();

    std::cout << "\nTotal objects created: " << BaseItem::GetCreatedCount() << '\n';
    return 0;
}
