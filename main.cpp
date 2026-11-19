#include "Character.hpp"
#include "DamagePolicies.hpp"
#include "GameExceptions.hpp"
#include "ISellable.hpp"
#include "Potion.hpp"
#include "QuestItem.hpp"
#include "Weapon.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <string>

namespace
{
    void PrintSection(const std::string& title)
    {
        std::cout << "\n===== " << title << " =====\n";
    }

    void SellThroughInterface(ISellable& item, const std::string& buyer)
    {
        std::cout << "Price: " << item.GetPrice() << " gold\n";
        item.Sell(buyer);
    }

    void TrySell(BaseItem& item, const std::string& buyer)
    {
        auto* sellable = dynamic_cast<ISellable*>(&item);
        if (sellable == nullptr)
        {
            throw NotSellableException{ item.GetName() };
        }

        sellable->Sell(buyer);
    }

    void DemoInterface()
    {
        PrintSection("1-2. Interface ISellable");

        Weapon sword{ "Sword", "Sharp steel blade", 15, ItemEffect{ "Fire", 5 } };
        Potion potion{ "Healing potion", "Restores health", 25, ItemEffect{ "Heal", 2 } };

        SellThroughInterface(sword, "Merchant");
        SellThroughInterface(potion, "Merchant");

        std::cout << "--- end of scope ---\n";
    }

    void DemoBinding()
    {
        PrintSection("3-4. Multiple inheritance, early and late binding");

        Weapon sword{ "Runic sword", "A sword with a runic edge", 15, ItemEffect{ "Fire", 5 } };
        const BaseItem& base = sword;

        // раннее связывание по типу ссылки
        std::cout << "GetCategory via BaseItem&: " << base.GetCategory() << '\n';
        std::cout << "GetCategory via Weapon:    " << sword.GetCategory() << '\n';

        // позднее связывание по настоящему типу объекта
        std::cout << "Describe via BaseItem& (Weapon::Describe runs):\n";
        base.Describe();

        std::cout << "--- end of scope ---\n";
    }

    void DemoDynamicCast()
    {
        PrintSection("5. dynamic_cast and exceptions: selling items");

        std::array<std::unique_ptr<BaseItem>, 3> items{
            std::make_unique<Weapon>("Bow", "Elven bow", 10, ItemEffect{ "Wind", 3 }),
            std::make_unique<Potion>("Mana potion", "Blue and bitter", 10, ItemEffect{ "Focus", 1 }),
            std::make_unique<QuestItem>("Golden key", "Opens the castle gate")
        };

        for (const auto& item : items)
        {
            try
            {
                TrySell(*item, "Merchant");
            }
            catch (const NotSellableException& error)
            {
                std::cout << "Refused: " << error.what() << '\n';
            }
            catch (const std::exception& error)
            {
                std::cout << "Error: " << error.what() << '\n';
            }
        }

        try
        {
            TrySell(*items[0], "Another merchant"); 
        }
        catch (const ItemAlreadySoldException& error)
        {
            std::cout << "Refused: " << error.what() << '\n';
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << '\n';
        }

        std::cout << "--- end of scope ---\n";
    }

    void DemoConfiguration()
    {
        PrintSection("6. Configuration: damage policy of the character");

        Character hero{ "Hero", 100, 100 };

        hero.TakeDamage(20);

        hero.SetDamagePolicy(std::make_unique<LightArmor>());
        hero.TakeDamage(20);

        hero.SetDamagePolicy(std::make_unique<HeavyArmor>());
        hero.TakeDamage(20);

        std::cout << "--- end of scope ---\n";
    }

    void DemoExceptions()
    {
        PrintSection("7. Exceptions: domain rules");

        try
        {
            Character ghost{ "Ghost", -5, 10 };
        }
        catch (const InvalidHealthException& error)
        {
            std::cout << "Character not created: " << error.what() << '\n';
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << '\n';
        }

        Character hero{ "Hero", 100, 100 };
        auto potion = std::make_shared<Potion>("Small potion", "Tastes like berries", 15, ItemEffect{ "Heal", 1 });
        auto sword = std::make_shared<Weapon>("Hero sword", "Plain but reliable", 14, ItemEffect{ "None", 0 });

        try
        {
            hero.AddItem(potion);
            hero.AddItem(potion);
        }
        catch (const DuplicateItemException& error)
        {
            std::cout << "Rule violated: " << error.what() << '\n';
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << '\n';
        }

        try
        {
            hero.UseItem(potion);
            hero.UseItem(sword);
        }
        catch (const ItemNotInInventoryException& error)
        {
            std::cout << "Rule violated: " << error.what() << '\n';
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << '\n';
        }

        hero.ShowLastUsedItem();

        try
        {
            hero.TakeDamage(-10);
        }
        catch (const InvalidDamageException& error)
        {
            std::cout << "Rule violated: " << error.what() << '\n';
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << '\n';
        }
    }
}

int main()
{
    DemoInterface();
    DemoBinding();
    DemoDynamicCast();
    DemoConfiguration();
    DemoExceptions();

    std::cout << "\nTotal objects created: " << BaseItem::GetCreatedCount() << '\n';
    return 0;
}