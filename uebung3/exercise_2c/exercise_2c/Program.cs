using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exercise_2c
{
    class Program
    {
        static void Main(string[] args)
        {

            IStateMaschine m = new StateMaschine();
            int lineNumber = 0;

            using (var fileStream = new StreamReader("code.txt"))
            {
                string line;

                while ((line = fileStream.ReadLine()) != null)
                {
                    int characterNumber = 0;
                    if (String.Empty != line)
                        foreach (var word in line.Split(' '))
                        {
                            IAtom atom = m.checkAtom(word, lineNumber, characterNumber);

                            Console.WriteLine($"The word {atom.AtomString}, Nr.:{characterNumber} line:{lineNumber}, is {atom.IsInGrammar} in this grammar");
                            //todo: maybe pull line and charNumber into atom
                            characterNumber = characterNumber + word.Length + 1;
                            lineNumber++;
                        }
                }
            }
        }
    }
}
