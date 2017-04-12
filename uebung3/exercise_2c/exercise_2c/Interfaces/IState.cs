using System.Collections.Generic;

namespace exercise_2c
{
    public enum StateTyp
    {
        start,
        normal,
        final
    }

    internal interface IState
    {

        StateTyp Type { get; }
        int StateNumber{ get; }
        IState processElement(IElement nextElement);
        void addTransition(ITransition trans);
        void addTransition(ICollection<ITransition> transList);
    }
}