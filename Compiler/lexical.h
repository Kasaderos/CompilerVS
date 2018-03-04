#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int NUM_WORDS = 9;

enum type_lex {
	LEX_NULL, // 0   
	LEX_ASSIGN, // 1
	LEX_INT, // 2
	LEX_FLOAT, LEX_PRINT,  // 3, 4, 
	LEX_PLUS, LEX_MINUS, LEX_NLINE, // 5, 6, 7
	LEX_FIN,
	LEX_FNUM, LEX_INUM,// 8
	LEX_ID, // 9
	POLIZ_ADDRESS, // 10
};

class Lex {
public:
	type_lex t_lex;
	string v_lex;
	Lex();
	Lex(type_lex t, string v);
	Lex(double f);
	Lex(int f);
	friend ostream & operator << (ostream & s, Lex lx);
	friend Lex operator + (const Lex & a, const Lex & b);
	friend Lex operator - (const Lex & a, const Lex & b);
};

Lex convert(const Lex & a);

class Ident {
public:
	type_lex type;
	string name;
	string val;
	bool declare;
	bool assign;
	Ident();
	explicit Ident(const string str);
};

class Table_ident {
public:
	vector< Ident > var;
	int put(Ident id);
};

class Scanner
{
	enum state { H, IDENT, NUM, DELIM };
	state ST;
	ifstream fp;
	string buf;
public:
	char c;
	char next;
	static type_lex types[];
	static const string LEXS[];
	static const string TWD[];
	void gc();
	int look();
	Scanner(const char * filename);
	Lex get_lex();
	~Scanner();
};

#endif
