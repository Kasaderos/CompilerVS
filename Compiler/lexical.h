#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include "enum.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

union value {
	int i;
	double d;
	string str;
	char ch;
	bool b;
	value(int i = 0);
	value(double d);
	value(string str);
	value(char ch);
	value(bool b);
};

class Lex {
public:
	type_lex t_lex;
	value v_lex;
	Lex();
	Lex(type_lex t, value v);
	Lex(double d);
	Lex(int i);
	friend ostream & operator << (ostream & s, Lex lx);
	friend Lex operator + (const Lex & a, const Lex & b);
	friend Lex operator - (const Lex & a, const Lex & b);
};

Lex convert(const Lex & a);

class Ident {
public:
	type_lex type;
	string name;
	value val;
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
