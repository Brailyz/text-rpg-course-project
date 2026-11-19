using Lab05;
using System;

namespace Lab05
{
    internal sealed class NoProtection : IDamagePolicy
    {
        public string Name => "без защиты";

        public int Reduce(int damage) => damage;
    }

    internal sealed class LightArmor : IDamagePolicy
    {
        private const int Reduction = 5;

        public string Name => "лёгкая броня";

        public int Reduce(int damage) => Math.Max(0, damage - Reduction);
    }

    internal sealed class HeavyArmor : IDamagePolicy
    {
        public string Name => "тяжёлая броня";

        public int Reduce(int damage) => damage / 2;
    }
}