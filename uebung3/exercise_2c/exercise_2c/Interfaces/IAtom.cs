using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exercise_2c
{
    interface IAtom
    {
        string AtomString { get; }
        bool IsInGrammar { get; set; }
        IElement getNext();
        bool hasNext();

    }
}
