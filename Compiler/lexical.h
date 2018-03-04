#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include "enum.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

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
	void print();
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
	static type_lex tw[];
	static type_lex td[];
	static const string LEXS[];
	static const string TD[];
	static const string TW[];
	void gc();
	int lookTW();
	int lookTD();
	Scanner(const char * filename);
	Lex get_lex();
	~Scanner();
};

#endif
