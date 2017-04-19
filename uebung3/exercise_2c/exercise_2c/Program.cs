using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace exercise_2c
{
    class Program
    {
        static void Main(string[] args)
        {

            IStateMaschine m = new StateMaschine();
            int lineNumber = 1;
            int file;
            string[] files;
            string fileName = string.Empty;

            do
            {
                files = Directory.GetFiles(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location), "*.txt");
                Console.WriteLine("Press number to open file:");
                for (int i = 0; i < files.Length; i++)
                {
                    Console.WriteLine($"{i + 1} -> {Path.GetFileName(files[i])}");
                }

                Int32.TryParse(Console.ReadLine(), out file);
                try
                {
                    fileName = files[file - 1];
                }catch(Exception e)
                {
                    Console.WriteLine("Fail while trying to get your file. Wrong input!");
                    Console.ReadKey();
                    Console.Clear();
                }
                
            } while (fileName == string.Empty);

            try
            {
                using (var fileStream = new StreamReader(fileName))
                {
                    string line;

                    while ((line = fileStream.ReadLine()) != null)
                    {
                        int characterNumber = 1;

                        if (String.Empty != line)
                            foreach (var word in line.Split(' '))
                            {
                                IAtom atom = m.checkAtom(word, lineNumber, characterNumber);

                                Console.WriteLine($"The word {atom.AtomString} -- Nr.:{characterNumber} line:{lineNumber}, is {atom.IsInGrammar} in this grammar\n");
                                characterNumber = characterNumber + word.Length + 1;
                            }
                        lineNumber++;
                    }
                }
            } catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
