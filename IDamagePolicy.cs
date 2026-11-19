using System;

namespace Lab05
{
    internal interface IDamagePolicy
    {
        string Name { get; }
        int Reduce(int damage);
    }
}
