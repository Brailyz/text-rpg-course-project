using System;
using System.Runtime.CompilerServices;
using System.Text;

namespace Lab04
{
    internal static class Program
    {
        [MethodImpl(MethodImplOptions.NoInlining)]
        private static void CreateTemporaryItem()
        {
            Potion temporary = new Potion("Временное зелье", "Исчезнет само", 1, new ItemEffect("Нет", 0));
            temporary.Use();
        }

        private static void Main()
        {
            using var logger = new Logger("Лабораторная работа 4");

            DemoPolymorphism(logger);
            DemoDeepCopy(logger);
            DemoShallowCopy(logger);
            DemoEquality(logger);
            DemoProtected(logger);
            DemoCharacter(logger);
            DemoStruct(logger);
            DemoGarbageCollector(logger);

            logger.Write($"Всего создано предметов: {BaseItem.GetCreatedCount()}");
        }

        private static void PrintSection(Logger logger, string title)
        {
            Console.WriteLine();
            logger.Write($"===== {title} =====");
        }

        private static void DemoPolymorphism(Logger logger)
        {
            PrintSection(logger, "1. Абстрактный класс и наследники");

            BaseItem[] items =
            {
                new Weapon("Рунный меч", "Клинок с рунами", 15, new ItemEffect("Огонь", 5)),
                new Potion("Малое зелье", "Пахнет ягодами", 25, new ItemEffect("Лечение", 2)),
                new Weapon("Лук", "Эльфийский лук", 10, new ItemEffect("Ветер", 3))
            };

            foreach (BaseItem item in items)
            {
                Console.WriteLine(item);
                item.Use();      
            }
        }

        private static void DemoDeepCopy(Logger logger)
        {
            PrintSection(logger, "2. Глубокая копия");

            Weapon axe = new Weapon("Топор", "Тяжёлый топор", 20, new ItemEffect("Лёд", 4));

            Weapon copy = new Weapon(axe);
            copy.SetEffectPower(100);
            Console.WriteLine($"Копия изменена до 100. Сила эффекта оригинала: {axe.Effect.Power}");

            Weapon clone = (Weapon)axe.Clone();
            axe.SetEffectPower(50).SetEffectPower(51);
            Console.WriteLine($"Оригинал изменён до 51. Оригинал: {axe.Effect.Power}, клон: {clone.Effect.Power}");
            Console.WriteLine($"Эффект общий? {ReferenceEquals(axe.Effect, clone.Effect)}");
        }

        private static void DemoShallowCopy(Logger logger)
        {
            PrintSection(logger, "3. Поверхностная копия");

            Potion elixir = new Potion("Эликсир", "Светящаяся жидкость", 30, new ItemEffect("Регенерация", 3));
            Potion elixirCopy = (Potion)elixir.Clone();

            elixirCopy.Effect.Power = 77;
            Console.WriteLine($"Копия изменена до 77. Оригинал: {elixir.Effect.Power}");
            Console.WriteLine($"Эффект общий? {ReferenceEquals(elixir.Effect, elixirCopy.Effect)}");
            Console.WriteLine($"Номера: оригинал {elixir.InventoryNumber}, копия {elixirCopy.InventoryNumber}");
        }

        private static void DemoEquality(Logger logger)
        {
            PrintSection(logger, "4. Сравнение по содержимому");

            Weapon swordA = new Weapon("Меч", "Первый экземпляр", 10, new ItemEffect("Огонь", 1));
            Weapon swordB = new Weapon("Меч", "Второй экземпляр", 10, new ItemEffect("Огонь", 1));
            Potion potion = new Potion("Меч", "Зелье с таким же названием", 5, new ItemEffect("Огонь", 1));

            Console.WriteLine($"ReferenceEquals(A, B): {ReferenceEquals(swordA, swordB)}");
            Console.WriteLine($"A.Equals(B): {swordA.Equals(swordB)}");
            Console.WriteLine($"Хеш-коды равны: {swordA.GetHashCode() == swordB.GetHashCode()}");
            Console.WriteLine($"A.Equals(зелье с тем же именем): {swordA.Equals(potion)}");
        }

        private static void DemoProtected(Logger logger)
        {
            PrintSection(logger, "5. protected: наследник меняет описание");

            Potion potion = new Potion("Настойка", "Крепкая настойка", 40, new ItemEffect("Бодрость", 1));

            potion.Dilute();
            Console.WriteLine(potion);
        }

        private static void DemoCharacter(Logger logger)
        {
            PrintSection(logger, "6. Персонаж и инвентарь");

            Character hero = new Character("Герой", 100, 100);

            Weapon sword = new Weapon("Меч героя", "Простой, но надёжный", 14, new ItemEffect("Нет", 0));
            Potion potion = new Potion("Зелье героя", "На вкус как ягоды", 15, new ItemEffect("Лечение", 1));
            Weapon sameSword = new Weapon("Меч героя", "Другой объект, то же содержимое", 14, new ItemEffect("Нет", 0));

            hero.AddItem(sword);
            hero.AddItem(potion);
            hero.AddItem(sameSword); 

            hero.UseItem(potion);
            hero.RemoveItem(potion);
            hero.UseItem(potion);

            Console.WriteLine(hero);
            Console.Write(hero.GetInventoryInfo());
        }

        private static void DemoStruct(Logger logger)
        {
            PrintSection(logger, "7. Структура:");

            Position start = new Position(0, 0);
            Position copy = start;
            copy.Move(5, 5);

            Console.WriteLine($"start = {start}, copy = {copy}");
        }

        private static void DemoGarbageCollector(Logger logger)
        {
            PrintSection(logger, "8. Сборщик мусора и финализатор");

            CreateTemporaryItem();

            GC.Collect();
            GC.WaitForPendingFinalizers();

            logger.Write("Сборка мусора выполнена.");
        }
    }
}
