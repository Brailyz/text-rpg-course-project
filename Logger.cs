using System;

namespace Lab05
{
    internal class Logger : IDisposable
    {
        private readonly string _name;

        public Logger(string name)
        {
            _name = name;
            Console.WriteLine($"Журнал '{_name}' открыт.");
        }

        public void Write(string message)
        {
            Console.WriteLine($"[{_name}] {message}");
        }

        public void Dispose()
        {
            Console.WriteLine($"Журнал '{_name}' закрыт.");
        }
    }
}

