#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include "enum.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Lex {
	type_lex t_lex;
	double v_lex;
public:
	Lex(type_lex t = LEX_NULL, double v = 0);
	Lex(int i);
	Lex(double d);
	type_lex get_type() const ;
	void set_type(type_lex t);
	double get_val() const;
	void set_val(double val);
	friend ostream & operator << (ostream & s, Lex lx);
	friend Lex operator + (const Lex & a, const Lex & b);
	friend Lex operator - (const Lex & a, const Lex & b);
	friend Lex operator * (const Lex & a, const Lex & b);
	friend Lex operator / (const Lex & a, const Lex & b);
};

Lex to_const(const Lex & a);

class Ident : public Lex{
public:
	string name;
	bool declare;
	bool assign;
	Ident();
	explicit Ident(string str);
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
