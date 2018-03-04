#include <iostream>
#include <stdio.h>
#include <fstream>
#include "lexical.h"
#include "syntax.h"
using namespace std;

Table_ident TID;

int main(int argc, char **argv)
{
	/*
	try {
	Parser parser("file.txt");
	parser.analyze();
	//parser.prog.print();
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
	}
	/*
	Scanner scan("file.txt");
	try{
	while (1){
	Lex t = scan.get_lex();
	cout << t << endl;
	if (t.t_lex == LEX_FIN)
	break;
	}
	}catch (char c){
	cout << c << endl;
	}*/
	//for (int i = 0; i != TID.var.size(); i++)
	//cout << i << " " << TID.var[i].name << endl;
	getchar();
	return 0;
}

