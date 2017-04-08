//==============================================================================
//  utilities   -  utility functions
//  last change:   06.10.02/Kp
//==============================================================================

#include <iostream>
#include <fstream>
using namespace std;

#include <limits.h>
#include <string.h>

#include "scanner.h"
#include "utilities.h"


//------------------------------------------------------------------------------
// getInputFile:  ask for input File name and open it
//------------------------------------------------------------------------------
void getInputFile(char *inFileName, fstream& inFile)
{
	bool ok;
	int c;
	do
	{
		ok = true;
		inFileName = "prg\\test1.pl0";

		//cout << endl << "Bitte Name der Eingabedatei eingeben:   ";
		//cin >> inFileName;

		//// add file extension, if necessary
		//if (stricmp(inFileName + strlen(inFileName) - 4, ".pl0"))
		//	strcat(inFileName, ".pl0");

		inFile.open(inFileName, ios::in);

		// test if open failed
		if (!inFile)
		{
			cout << "Error: cannot open file " << inFileName << endl;
			inFile.clear();
			ok = false;
		}
		else
		{
			// test if file opened for input is empty
			c = inFile.get(); inFile.putback((char)c);
			if (inFile.eof())
			{
				cout << "Error: File " << inFileName << " does not exist or is empty !";
				inFile.close();
				inFile.clear();
				ok = false;
			}
		}
	} while (!ok);
}

//------------------------------------------------------------------------------
//  weiter  -  Wartet Drücken der ENTER-Taste ab, ignoriert alles andere
//------------------------------------------------------------------------------
void weiter(void)
{
	cout << "\n>>";                 // Prompt ausgeben
	cin.ignore(INT_MAX, '\n');     // alles bis ENTER ignorieren
}

