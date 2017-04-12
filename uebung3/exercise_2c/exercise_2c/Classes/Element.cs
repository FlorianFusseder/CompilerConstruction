using System;

namespace exercise_2c
{
    internal class Element
        : IElement
    {
        public int CharPos { get; }

        public int LinePos { get; }

        public string Elem { get; }

        public Element(char c, int line, int row)
            : this(c.ToString(), line, row)
        {

        }

        public Element(string s, int line, int row)
        {
            this.Elem = s;
            this.LinePos = line;
            this.CharPos = row;
        }
    }
}