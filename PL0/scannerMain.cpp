//==============================================================================
//  scannerMain.cpp   -   test frame for the scanner
//  last change:   06.10.02/Kp
//==============================================================================

#include <iostream>
#include <fstream>
using namespace std;

#include "scanner.h"
#include "utilities.h"

int main()
{
	Scanner S;

	// The Scanner protocol reports all tokens and number constants
	// during the lexical analysis
	S.setScannerProtocol(on);

	cout << "\nLexikalische Analyse fuer PL/0";
	cout << "\n------------------------------\n";
	do
	{
		S.getSym();
	} while (S.sym != period);
	cout << "End of program reached !" << endl;
	weiter();
	return 0;

}


