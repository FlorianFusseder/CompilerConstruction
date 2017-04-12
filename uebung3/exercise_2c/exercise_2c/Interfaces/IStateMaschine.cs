using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exercise_2c
{
    interface IStateMaschine
    {
        IAtom checkAtom(string s, int lineNumber, int rowNumber);
    }
}
