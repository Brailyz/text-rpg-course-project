using System;

namespace Lab05
{
    internal static class Program
    {
        private static void Main()
        {
            using Logger logger = new Logger("Лабораторная работа 5");

            DemoInterface(logger);
            DemoBinding(logger);
            DemoTypeCheck(logger);
            DemoComparable(logger);
            DemoConfiguration(logger);
            DemoExceptions(logger);

            logger.Write($"Всего создано предметов: {BaseItem.GetCreatedCount()}");
        }

        private static void PrintSection(Logger logger, string title)
        {
            Console.WriteLine();
            logger.Write($"===== {title} =====");
        }

        private static void SellThroughInterface(ISellable item, string buyer)
        {
            Console.WriteLine($"Цена: {item.Price} золота.");
            item.Sell(buyer);
        }

        private static void TrySell(BaseItem item, string buyer)
        {
            if (item is ISellable sellable)
            {
                sellable.Sell(buyer);
            }
            else
            {
                throw new NotSellableException(item.Name);
            }
        }

        private static void DemoInterface(Logger logger)
        {
            PrintSection(logger, "1-2. Интерфейс ISellable, код работает через контракт");

            Weapon sword = new Weapon("Меч", "Стальной клинок", 15, new ItemEffect("Огонь", 5));
            Potion potion = new Potion("Лечебное зелье", "Восстанавливает здоровье", 25, new ItemEffect("Лечение", 2));

            SellThroughInterface(sword, "Торговец");
            SellThroughInterface(potion, "Торговец");
        }

        private static void DemoBinding(Logger logger)
        {
            PrintSection(logger, "3-4. Множественное наследование, раннее и позднее связывание");

            Weapon sword = new Weapon("Рунный меч", "Клинок с рунами", 15, new ItemEffect("Огонь", 5));
            BaseItem baseRef = sword;

            Console.WriteLine($"GetCategory через BaseItem: {baseRef.GetCategory()}");
            Console.WriteLine($"GetCategory через Weapon:   {sword.GetCategory()}");

            Console.WriteLine($"Describe через BaseItem: {baseRef.Describe()}");
        }

        private static void DemoTypeCheck(Logger logger)
        {
            PrintSection(logger, "5. Проверка типа: is и as");

            BaseItem[] items =
            {
                new Weapon("Лук", "Эльфийский лук", 10, new ItemEffect("Ветер", 3)),
                new Potion("Зелье маны", "Синее и горькое", 10, new ItemEffect("Фокус", 1)),
                new QuestItem("Золотой ключ", "Открывает ворота замка")
            };

            foreach (BaseItem item in items)
            {
                try
                {
                    TrySell(item, "Торговец");
                }
                catch (NotSellableException e)
                {
                    Console.WriteLine($"Отказ: {e.Message}");
                }
                catch (GameRuleException e)
                {
                    Console.WriteLine($"Нарушено правило: {e.Message}");
                }
            }

            try
            {
                TrySell(items[0], "Другой торговец");  
            }
            catch (ItemAlreadySoldException e)
            {
                Console.WriteLine($"Отказ: {e.Message}");
            }
            catch (GameRuleException e)
            {
                Console.WriteLine($"Нарушено правило: {e.Message}");
            }

            ISellable maybe = items[2] as ISellable;
            Console.WriteLine($"Ключ as ISellable: {(maybe == null ? "null" : "продаваем")}");
        }

        private static void DemoComparable(Logger logger)
        {
            PrintSection(logger, "6. IComparable: упорядочивание по названию");

            BaseItem[] items =
            {
                new Weapon("Топор", "Тяжёлый топор", 20, new ItemEffect("Лёд", 4)),
                new Potion("Эликсир", "Светящаяся жидкость", 30, new ItemEffect("Регенерация", 3)),
                new Weapon("Арбалет", "Точный и тугой", 12, new ItemEffect("Яд", 2))
            };

            Array.Sort(items);

            foreach (BaseItem item in items)
            {
                Console.WriteLine(item.Name);
            }
        }

        private static void DemoConfiguration(Logger logger)
        {
            PrintSection(logger, "7. Конфигурирование: правило снижения урона");

            Character hero = new Character("Герой", 100, 100);

            hero.TakeDamage(20);

            hero.Policy = new LightArmor();
            hero.TakeDamage(20);

            hero.Policy = new HeavyArmor();
            hero.TakeDamage(20);
        }

        private static void Attempt(Logger journal, string title, Action action)
        {
            try
            {
                action();
                journal.Write($"{title}: успешно");
            }
            catch (GameRuleException e)
            {
                journal.Write($"{title}: нарушено правило — {e.Message}");
            }
            finally
            {
                journal.Write($"{title}: попытка завершена");
            }
        }

        private static void DemoExceptions(Logger logger)
        {
            PrintSection(logger, "8. Исключения: try / catch / finally / using");

            try
            {
                Character ghost = new Character("Призрак", -5, 10);
            }
            catch (InvalidHealthException e)
            {
                Console.WriteLine($"Персонаж не создан: {e.Message}");
            }

            Character hero = new Character("Герой", 100, 100);
            Potion potion = new Potion("Малое зелье", "Пахнет ягодами", 15, new ItemEffect("Лечение", 1));
            Weapon sword = new Weapon("Меч героя", "Простой, но надёжный", 14, new ItemEffect("Нет", 0));

            using (Logger journal = new Logger("Журнал событий"))
            {
                Attempt(journal, "Добавить зелье", () => hero.AddItem(potion));
                Attempt(journal, "Добавить зелье снова", () => hero.AddItem(potion));
                Attempt(journal, "Выпить зелье", () => hero.UseItem(potion));
                Attempt(journal, "Применить меч вне инвентаря", () => hero.UseItem(sword));
                Attempt(journal, "Отрицательный урон", () => hero.TakeDamage(-10));
            }

            Console.WriteLine(hero);
        }
    }
}
