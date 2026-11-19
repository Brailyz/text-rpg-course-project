using System;

namespace Lab05
{
    internal interface ISellable
    {
        int Price { get; }
        bool IsSold { get; }
        void Sell(string buyer);
    }
}