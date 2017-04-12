using System;
using System.Collections.Generic;

namespace exercise_2c
{
    internal class Transition
        : ITransition
    {

        public IState next { get; private set; }
        public IList<string> transChars { get; private set; }

        public Transition(IState next, string transChar)
            : this(next, new List<string> { transChar})
        {

        }

        public Transition(IState next, IList<string> transChars)
        {
            this.next = next;
            this.transChars = transChars;
        }

        public IState checkTransition(IElement elem)
        {
            return (this.transChars.Contains(elem.Elem)) ? this.next : null;
        }
    }
}