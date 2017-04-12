using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exercise_2c
{
    internal class Atom
        : IAtom
    {
        private string atom;
        private readonly int lineNumber;
        private readonly int rowNumber;
        private bool isLegit;
        private readonly ICollection<IElement> atoms;

        int pointer = 0;

        public string AtomString
        {
            get { return atom; }
        }

        public bool IsInGrammar
        {
            get
            {
                return isLegit;
            }

            set
            {
                isLegit = value;
            }
        }

        public Atom(string atom, int lineNumber, int rowNumber)
        {
            this.atom = atom;


            this.lineNumber = lineNumber;
            this.rowNumber = rowNumber;
            isLegit = false;
            atoms = new List<IElement>();

            foreach (var item in atom)
            {
                atoms.Add(new Element(item, lineNumber, rowNumber++));
            }
        }

        public bool hasNext()
        {
            return pointer < atom.Length;
        }

        public IElement getNext()
        {
            return atoms.ElementAt(pointer++);
        }
    }
}
