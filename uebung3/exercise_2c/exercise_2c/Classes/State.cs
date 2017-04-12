using System;
using System.Collections.Generic;
using System.Linq;

namespace exercise_2c
{

    internal class State
        : IState
    {
        private readonly int stateNumber;
        private readonly StateTyp typ;
        private ICollection<ITransition> transList;

        public int StateNumber
        {
            get { return stateNumber; }
        }

        public StateTyp Type
        {
            get
            {
                return typ;
            }
        }

        public State(int stateNumber)
            : this(stateNumber, StateTyp.normal)
        {
        }

        public State(int stateNumber, StateTyp typ)
        {
            this.stateNumber = stateNumber;
            this.typ = typ;
            this.transList = new List<ITransition>();
        }

        public IState processElement(IElement nextElement)
        {
            IState nextState = null;
            foreach (var item in transList)
            {
                nextState = item.checkTransition(nextElement);
                if (nextState != null)
                {
                    Console.WriteLine($"The Element: \"{nextElement.Elem}\" at line:{nextElement.LinePos} position:{nextElement.CharPos} at State:{this.StateNumber} to State:{nextState.StateNumber}");
                    return nextState;
                }
                    
            }

            if (nextState == null)
                Console.WriteLine($"The Element: {nextElement.Elem} at line:{nextElement.LinePos} position:{nextElement.CharPos} has no Transition at State:{this.StateNumber}.");

            return nextState;
        }

        public void addTransition(ITransition trans)
        {
            this.transList.Add(trans);
        }

        public void addTransition(ICollection<ITransition> addTransList)
        {
            foreach (var item in addTransList)
            {
                addTransition(item);
            }
        }

    }
}