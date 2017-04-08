//==============================================================================
//   scanner.cpp    Lexical Analysis for PL/0  -
//   extended version:  eliminates comments
//                      allows decimal and floating point constants
//   last change:   06.10.02/Kp
//==============================================================================

#include <iostream>
#include <fstream>
using namespace std;

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <iomanip>
#include "scanner.h"
#include "utilities.h"

//------------------------------------------------------------------------------
// Getchar:  Puts the next source character into ch
//------------------------------------------------------------------------------
void Scanner::getChar(void)
{
	// refill line buffer ist it is empty
	if (linePos == lineLen) 					// input buffer empty ?
	{
		if (inFile.eof())
		{
			cout << "\n ---- Error: premature end of file ! ----";
			weiter();
			exit(1);
		}
		lineLen = 0; 							// fetch next source code record
		linePos = 0;
		lineNr++;
		inFile.getline(line, LINMAX);           // get next line from sorce file
		cout << setw(3) << lineNr << ":  " << line << endl;
		strcat_s(line, " ");                      // attach " " at end of line
		lineLen = strlen(line);
	}
	// return next character to function getSym
	ch = line[linePos++];   					// get actual character and
												// point to next character
}

//------------------------------------------------------------------------------
// Getsym:   Provides the next symbol from the source program.
//           Puts the results into the following variables:
//	sym:     next symbol (internal representation)
//	id :     last identifier or reserved word as string of length CMAX
//	num :    numerical value of last number
//------------------------------------------------------------------------------
void Scanner::getSym()
{
	int i, j, k;
	unsigned char d;
	float dnum;       // used to evaluate decimal numbers
	int quot;         // used to evaluate decimal numbers
	int  exp;         // used to evaluate exponent of float numbers
	int  expflag;     // used to evaluate exponent of float numbers

start:
	while (ch == ' ') { getChar(); } 			// proceed to next character

	//  new:  eliminate comments
	//  ========================
	if (ch == '/')
	{
		getChar();
		if (ch != '*')
			sym = slash;
		else
		{
			getChar();
			do
			{
				while (ch != '*') { getChar(); }
				getChar();
			} while (ch != '/');
			getChar();
			goto start;
		}
	}

	switch (charType[ch])
	{
	case letter:  for (i = 0; i < CMAX; i++) id[i] = ' ';
		id[CMAX] = '\0';             // initialize identifier name
		k = 0;
		do 						// get identifier or reserved word
		{
			if (k < CMAX) { id[k++] = ch; }
			getChar();
		} while ((charType[ch] == letter) || (charType[ch] == digit));

		i = 0; j = NORW - 1;  		    // test for reserved word
		do
		{
			k = (i + j) / 2;          // compare case insensitive !
			if (_stricmp(id, word[k]) <= 0) j = k - 1;
			if (_stricmp(id, word[k]) >= 0) i = k + 1;
		} while (i <= j);
		if (i - 1 > j)
			sym = wsym[k]; 		    // symbol is a reserved word
		else
			sym = ident;			// symbol is an identifier
		break;

		/***********************************************************************

		// new:  Analysis of numbers decimal constants p.e.   25.25
		// ========================================================
		case digit:   sym = number;  			// symbol is a number
					  dnum = 0;                  // initialize numerical value to 0
					  do                         // evaluate number value
					  {
						d = (unsigned char)(ch - '0');
						dnum = dnum*10 + d;
						getChar();
					  } while (charType[ch]==digit);
					  if (ch == '.')
					  {  quot=1;
						 getChar();
						 d = (unsigned char)(ch - '0');
						 if (charType[ch]!=digit)
						 {   cout << "\n ---- Error: syntax error in number ! ---- ";
							 cout << endl;
							 sym=nul;
							 break;
						 }
						 do
						 {   dnum = dnum*10 + d;
							 quot*=10;
							 getChar();
							 d = (unsigned char)(ch - '0');
						 } while (charType[ch]==digit);
						 dnum = dnum/quot;
					  }
					  cout << "\n ---- dnum = " << dnum << " ----  \n" ;
					  break;
		***********************************************************************/


		// new:  Analysis of floating numbers, i.e.  12.34E+78
		// ===================================================
	case digit:   sym = number;  			// symbol is a number
		dnum = 0;                  // initialize numerical value to 0
		do                         // evaluate number value
		{
			d = (unsigned char)(ch - '0');
			dnum = dnum * 10 + d;
			getChar();
		} while (charType[ch] == digit);
		if (ch == '.')
		{
			quot = 1;
			getChar();
			d = (unsigned char)(ch - '0');
			if (charType[ch] != digit)
			{
				cout << "\n ---- Error: syntax error in number ! ---- ";
				cout << endl;
				sym = nul;
				break;
			}
			do
			{
				dnum = dnum * 10 + d;
				quot *= 10;
				getChar();
				d = (unsigned char)(ch - '0');
			} while (charType[ch] == digit);
			dnum = dnum / quot;
		}
		if (ch == 'E')
		{
			exp = 0; expflag = 1;
			getChar();
			if (ch == '+') getChar();
			if (ch == '-') { getChar(); expflag = -1; }
			if (!charType[ch] == digit)
			{
				cout << "\n ---- Error: syntax error in number ! ---- ";
				cout << endl;
				sym = nul;
				break;
			}
			do
			{
				d = (unsigned char)(ch - '0');
				exp = 10 * exp + d;
				getChar();
			} while (charType[ch] == digit);
			j = 1;
			for (i = 1; i <= exp; i++)
				j = j * 10;
			if (expflag == 1) dnum = dnum * j;
			else            dnum = dnum / j;
		}
		cout << "\n ---- dnum = " << dnum << " ----  \n";
		break;
	case special:
	case other:   switch (ch)
	{
	case ':':   getChar();
		if (ch == '=')     // ":=" -operator
		{
			sym = becomes; getChar();
		}
		else
		{
			sym = nul;
		}  // error
		break;

	case '>':   getChar();
		if (ch == '=')     // ">=" - operator
		{
			sym = geq; getChar();
		}
		else               // ">" - operator
		{
			sym = gtr;
		}
		break;

	case '<':   getChar();
		if (ch == '=')     // "<=" - operator
		{
			sym = leq; getChar();
		}
		else               // "<" - operator
		{
			sym = lss;
		}
		break;

	default:    sym = ssym[ch];	   // special  or other symbol
		getChar();
	}
	}
	scannerProtocol();
}

//------------------------------------------------------------------------------
// Scanner:  constructor, initializes the scanner data objects
//------------------------------------------------------------------------------
Scanner::Scanner()
{
	unsigned c;

	// initialize Scanner Daten structures
	lineLen = 0;
	linePos = 0;
	lineNr = 0;
	ch = ' ';
	scannerPrt = off;

	// table of reserved words
	strcpy_s(word[0], "begin     ");
	strcpy_s(word[1], "call      ");
	strcpy_s(word[2], "const     ");
	strcpy_s(word[3], "do        ");
	strcpy_s(word[4], "end       ");
	strcpy_s(word[5], "if        ");
	strcpy_s(word[6], "odd       ");
	strcpy_s(word[7], "procedure ");
	strcpy_s(word[8], "then      ");
	strcpy_s(word[9], "var       ");
	strcpy_s(word[10], "while     ");

	// internal representation of reserved words
	wsym[0] = beginSym;
	wsym[1] = callSym;
	wsym[2] = constSym;
	wsym[3] = doSym;
	wsym[4] = endSym;
	wsym[5] = ifSym;
	wsym[6] = oddSym;
	wsym[7] = procSym;
	wsym[8] = thenSym;
	wsym[9] = varSym;
	wsym[10] = whileSym;



	// internal representation of special symbols
	for (c = 0; c < CHSIZE; c++)  
		ssym[c] = nul;

	ssym['+'] = symbol::plus;
	ssym['-'] = symbol::minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym[')'] = rparen;
	ssym['.'] = period;
	ssym['#'] = neq;
	ssym['='] = eql;
	ssym[','] = comma;
	ssym['<'] = lss;
	ssym['>'] = gtr;
	ssym[';'] = semicolon;

	// table of character types
	for (c = 0; c < CHSIZE; c++) {
		if (isalpha(c))
			charType[c] = letter;
		else if
			(isdigit(c)) charType[c] = digit;
		else
			charType[c] = other;
	}

		charType['_'] = letter;
		charType['.'] = special;
		charType['<'] = special;
		charType['>'] = special;
		charType['('] = special;
		charType['*'] = special;
		charType['+'] = special;
		charType['-'] = special;
		charType['='] = special;
		charType[')'] = special;
		charType[','] = special;
		charType[';'] = special;
		charType['/'] = special;
		charType['#'] = special;

		// table of printabele symbol names for the protocols
		strcpy_s(symNames[nul], "nul ");
		strcpy_s(symNames[ident], "ident ");
		strcpy_s(symNames[number], "number ");
		strcpy_s(symNames[symbol::plus], "plus ");
		strcpy_s(symNames[symbol::minus], "minus ");
		strcpy_s(symNames[times], "times ");
		strcpy_s(symNames[slash], "slash ");
		strcpy_s(symNames[oddSym], "oddSym ");
		strcpy_s(symNames[eql], "eql ");
		strcpy_s(symNames[neq], "neq ");
		strcpy_s(symNames[lss], "lss ");
		strcpy_s(symNames[leq], "leq ");
		strcpy_s(symNames[gtr], "gtr ");
		strcpy_s(symNames[geq], "geq ");
		strcpy_s(symNames[lparen], "lparen ");
		strcpy_s(symNames[rparen], "rparen ");
		strcpy_s(symNames[comma], "comma ");
		strcpy_s(symNames[semicolon], "semicolon ");
		strcpy_s(symNames[period], "period ");
		strcpy_s(symNames[becomes], "becomes ");
		strcpy_s(symNames[beginSym], "beginSym ");
		strcpy_s(symNames[endSym], "endSym ");
		strcpy_s(symNames[ifSym], "ifSym ");
		strcpy_s(symNames[thenSym], "thenSym ");
		strcpy_s(symNames[whileSym], "whileSym ");
		strcpy_s(symNames[doSym], "doSym ");
		strcpy_s(symNames[callSym], "callSym ");
		strcpy_s(symNames[constSym], "constSym ");
		strcpy_s(symNames[varSym], "varSym ");
		strcpy_s(symNames[procSym], "procSym ");

		// open source file
		getInputFile(inFileName, inFile);
}

//------------------------------------------------------------------------------
// symProtocol:  print a symbol name in readable form
//------------------------------------------------------------------------------
void Scanner::scannerProtocol(void)
{
	if (scannerPrt == on)
	{
		cout << symNames[sym];
		if (!(linePos == lineLen)) return;
		cout << "\n"; weiter();
	}
}