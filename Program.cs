using System;
using System.Runtime.CompilerServices;

namespace Lab03
{
    internal class Program
    {
        [MethodImpl(MethodImplOptions.NoInlining)]
        static void CreateTemporaryItem()
        {
            Item temp = new Item("Временный предмет", "Исчезает без ссылок");
            Console.WriteLine($"Создан: {temp.Name}. Выход из метода.");
        }

        static void Main()
        {
            Console.WriteLine("Композиция");
            Character character = new Character("Артур", 100, 100);
            Console.WriteLine(character);
            Console.Write(character.GetInventoryInfo());

            Console.WriteLine();
            Console.WriteLine("Агрегация");
            Item sword = new Item("Меч", "Острый стальной меч");
            Item potion = new Item("Зелье", "Восстанавливает здоровье");

            Console.WriteLine();
            character.AddItem(sword);
            character.AddItem(potion);

            Console.WriteLine();
            Console.Write(character.GetInventoryInfo());

            Console.WriteLine();
            character.UseItem(sword);

            Console.WriteLine();
            Console.WriteLine("Проверки правил: корректное действие и отказ");

            Console.WriteLine("Урон");
            character.TakeDamage(30);
            Console.WriteLine(character);
            character.TakeDamage(-5);
            Console.WriteLine(character);

            Console.WriteLine();
            Console.WriteLine("Добавление");
            character.AddItem(sword);
            character.AddItem(null);

            Console.WriteLine();
            Console.WriteLine("Удаление");
            character.RemoveItem(potion);
            Console.Write(character.GetInventoryInfo());
            character.RemoveItem(potion);
            character.UseItem(potion);

            Console.WriteLine();
            Console.WriteLine("Предмет жив после удаления из инвентаря");
            potion.Use();

            Console.WriteLine();
            Console.WriteLine("Некорректные данные в конструкторе");
            Character broken = new Character("Баг", -10, 50);
            Console.WriteLine(broken);

            Console.WriteLine();
            Console.WriteLine("Ссылки и копии");
            Character first = new Character("Мерлин", 80, 100);
            Character second = first;

            Console.WriteLine($"До:    first = {first}");
            Console.WriteLine($"       second = {second}");

            second.TakeDamage(25);

            Console.WriteLine($"После: first = {first}");
            Console.WriteLine($"       second = {second}");
            Console.WriteLine($"Ссылки совпадают: {ReferenceEquals(first, second)}");

            Console.WriteLine();
            Console.WriteLine("Структура: копирование значения");
            Position p1 = new Position(1, 2);
            Position p2 = p1;

            Console.WriteLine($"До:    p1 = {p1}, p2 = {p2}");

            p2.Move(10, 10);

            Console.WriteLine($"После: p1 = {p1}, p2 = {p2}");

            Console.WriteLine();
            Console.WriteLine("IDisposable и using");
            Character fighter = new Character("Ланселот", 100, 100);

            using (Logger log = new Logger("Журнал боя"))
            {
                log.Write($"До удара: {fighter}");

                fighter.TakeDamage(40);
                log.Write($"После удара: {fighter}");

                fighter.TakeDamage(-10);
                log.Write("Отрицательный урон отклонён");
            }

            Console.WriteLine("После блока");

            Console.WriteLine();
            Console.WriteLine("Сборщик мусора");
            CreateTemporaryItem();
            Console.WriteLine("Метод завершён: ссылок на предмет больше нет.");
            Console.WriteLine("Деструктор пока не сработал.");

            GC.Collect();
            GC.WaitForPendingFinalizers();

            Console.WriteLine("Сборка мусора выполнена.");
        }
    }
}