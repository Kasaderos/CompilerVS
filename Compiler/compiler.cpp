#include <iostream>
#include <stdio.h>
#include <fstream>
#include "lexical.h"
#include "syntax.h"
using namespace std;

Table_ident TID;
void check_scan();
int main(int argc, char **argv)
{
	Interpretator interpretator("file.txt");
	try {
		interpretator.interpretation();
	}
	catch (Lex lex) {
		cout << Scanner::LEXS[lex.get_type()] << " error" << endl;
	}
	catch (const char * str) {
		cout << str << endl;
	}
	catch (string str) {
		cout << str << endl;
	}
	//check_scan();
	getchar();
	return 0;
}

void check_scan() {
	Scanner scan("file.txt");
	try {
		while (1) {
			Lex t = scan.get_lex();
			cout << t << endl;
			if (t.get_type() == LEX_FIN)
				break;
		}
	}
	catch (char c) {
		cout << "error" << c << endl;
	}
	TID.print();
}