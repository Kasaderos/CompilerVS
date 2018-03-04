#include <iostream>
#include <stdio.h>
#include <fstream>
#include "lexical.h"
//#include "syntax.h"
using namespace std;

Table_ident TID;

int main(int argc, char **argv)
{
	/*
	Interpretator interpretator("file.txt");
	try {
		interpretator.interpretation();
	}
	catch (Lex lex) {
		cout << Scanner::LEXS[lex.t_lex] << " error" << endl;
	}
	catch (const char * str) {
		cout << str << endl;
	}
	catch (string str) {
		cout << str << endl;
	}*/
	Scanner scan("file.txt");
	try {
		while (1) {
			Lex t = scan.get_lex();
			cout << t << endl;
			if (t.t_lex == LEX_FIN)
				break;
		}
	}
	catch (char c) {
		cout << c << endl;
	}
	getchar();
	return 0;
}

