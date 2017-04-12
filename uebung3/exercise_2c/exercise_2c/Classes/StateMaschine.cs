using System;
using System.Collections.Generic;

namespace exercise_2c
{
    internal class StateMaschine
        : IStateMaschine
    {

        private IState recentState;

        private IState q0;
        private IState q1;
        private IState q2;
        private IState q3;
        private IState q4;
        private IState q5;
        private IState q6;
        private IState q7;
        public StateMaschine()
        {
            q0 = new State(0, StateTyp.start);
            q1 = new State(1, StateTyp.final);
            q2 = new State(2, StateTyp.final);
            q3 = new State(3, StateTyp.final);
            q4 = new State(4);
            q5 = new State(5);
            q6 = new State(6);
            q7 = new State(7, StateTyp.final);

            q0.addTransition(new List<ITransition>
            {
                new Transition(q1, new List<string> { "1", "2", "3", "4", "5", "6", "7", "8", "9" }),
                new Transition(q2, "0" ),
                new Transition(q3, "." ),
            });

            q1.addTransition(new List<ITransition>
            {
                new Transition(q1, new List<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }),
                new Transition(q3, "." ),
            });

            q2.addTransition(new List<ITransition>
            {
                new Transition(q3, "." ),
            });

            q3.addTransition(new List<ITransition>
            {
                new Transition(q4, new List<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }),
            });

            q4.addTransition(new List<ITransition>
            {
                new Transition(q4, new List<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }),
                new Transition(q5, "E" ),
            });

            q5.addTransition(new List<ITransition>
            {
                new Transition(q6, new List<string> {"+", "-" }),
            });

            q6.addTransition(new List<ITransition>
            {
                new Transition(q7, new List<string> { "1", "2", "3", "4", "5", "6", "7", "8", "9" }),
            });

            q7.addTransition(new List<ITransition>
            {
                new Transition(q7, new List<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }),
            });
        }

        public IAtom checkAtom(string s, int lineNumber, int rowNumber)
        {

            IAtom atom = new Atom(s, lineNumber, rowNumber);
            recentState = q0;

            while (recentState != null && atom.hasNext())
                recentState = recentState.processElement(atom.getNext());

            if (recentState != null && recentState.Type.HasFlag(StateTyp.final))
                atom.IsInGrammar = true;

            return atom;
        }
    }
}