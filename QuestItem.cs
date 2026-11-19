using Lab05;
using System;
using System.Xml.Linq;

namespace Lab05
{
    internal sealed class QuestItem : BaseItem
    {
        public QuestItem(string name, string description)
            : base(name, description)
        {
        }

        public override void Use()
        {
            Console.WriteLine($"Вы осматриваете {Name}: наверняка где-то пригодится.");
        }

        public override BaseItem Clone()
        {
            return ShallowCopy();
        }
    }
}