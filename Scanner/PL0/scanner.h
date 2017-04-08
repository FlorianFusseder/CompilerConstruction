//==============================================================================
//  scanner.h:     declarations for the scanner
//  last change:   06.10.02/Kp
//==============================================================================
#if !defined (__scanner_h)
#define __scanner_h

#include <fstream>

// general constants
const int NORW = 11;		//number of reserved words
const int TXMAX = 100;		//maximum value for symbol table index
const int IMAX = 32767;		//maximum integer value
const int DMAX = 14;		//maximum nuber of digits for integers
const int CMAX = 10;		//maximum lengt of character fields
const int SMAX = 50;		//maximum number of symbol elements
const int FNMAX = 100;		// maximale Länge von Dateinamen
const int LINMAX = 100;		// maximale Länge einer Zeile
const int CHSIZE = 256;		//size of character set
const int NESTMAX = 3;		//maximum depth of block nesting
const int CODEMAX = 200;	//maximum length of intermediate code

enum symbol {
	nul, ident, number, plus, minus, times, slash, oddSym,
	eql, neq, lss, leq, gtr, geq, lparen, rparen, comma,
	semicolon, period, becomes, beginSym, endSym, ifSym,
	thenSym, whileSym, doSym, callSym, constSym, varSym,
	procSym
};                    //  less than SMAX symbols !
					   // input char types:
enum cType { letter, digit, special, other };
enum onOff { on, off };

class Scanner
{
public:
	Scanner();
	~Scanner() { inFile.close(); }

	void getSym();
	void setScannerProtocol(onOff flag) { 
		scannerPrt = flag; 
	}

	// scanner result values
	symbol		sym;					// last symbol/token read by the scanner
	char		id[CMAX + 1];				// last identifier read by scanner
	int			num;					// last number read by the scanner

	// scanner-Tables
	char		word[NORW][CMAX + 1];	    // list of reserved words
	symbol		wsym[NORW];				// internal representation of reserved words
	symbol		ssym[CHSIZE];			// list of special symbols
	cType 		charType[CHSIZE];		// source character types

	// file management
	fstream  	inFile;					// source file stream object
	char     	inFileName[FNMAX + 1];    // name of the source file

private:
	void 		getChar(void);
	void        scannerProtocol(void);  // print out actual symbol name

	// source line buffer management
	char		line[LINMAX];			// source line buffer
	int			lineLen;				// actual source line lentgth
	int			linePos;				// actual position in input buffer
	int			lineNr;					// actual source line number
	char		ch;	    				// last character read

	// translation table for protocols
	char        symNames[SMAX][CMAX + 10]; // symbol names in readable form
	onOff       scannerPrt;
};

#endif
