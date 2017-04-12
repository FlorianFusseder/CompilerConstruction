namespace exercise_2c
{
    internal interface ITransition
    {
        IState checkTransition(IElement elem);
    }
}