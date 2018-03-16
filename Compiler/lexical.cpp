#include <string>
#include "lexical.h"
using namespace std;

extern Table_ident TID;

Ident::Ident() : declare(false), assign(false) {}

Ident::Ident(string str) : name(str.c_str()), declare(false), assign(false) {}

Lex::Lex(type_lex t, double v) {
	t_lex = t;
	v_lex = v;
}

Lex::Lex(int i) {
	t_lex = LEX_INUM;
	v_lex = i;
}

Lex::Lex(double d) {
	t_lex = LEX_FNUM;
	v_lex = d;
}

type_lex Lex::get_type() const {
	return t_lex;
}

void Lex::set_type(type_lex t) {
	t_lex = t;
}
double Lex::get_val() const {
	return v_lex;
}

void Lex::set_val(double val) {
	v_lex = val;
}

Lex to_const(const Lex & a) {
	if (a.get_type() == LEX_ID) {
		int i = (int)a.get_val();
		if (TID.var[i].get_type() == LEX_INT)
			return (int)TID.var[i].get_val();
		else
			return TID.var[i].get_val();
	}
	return a;
}

Lex operator + (const Lex & a, const Lex & b) {
	Lex lex1 = to_const(a);
	Lex lex2 = to_const(b);
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return lex1.get_val() + lex2.get_val();
	return (int)lex1.get_val() + (int)lex2.get_val();
}

Lex operator - (const Lex & a, const Lex & b) {
	Lex lex1 = to_const(a);
	Lex lex2 = to_const(b);
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return lex1.get_val() - lex2.get_val();
	return (int)lex1.get_val() - (int)lex2.get_val();
}

Lex operator * (const Lex & a, const Lex & b){
	Lex lex1 = to_const(a);
	Lex lex2 = to_const(b);
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return lex1.get_val() * lex2.get_val();
	return (int)lex1.get_val() * (int)lex2.get_val();
}
Lex operator / (const Lex & a, const Lex & b){
	Lex lex1 = to_const(a);
	Lex lex2 = to_const(b);
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return lex1.get_val() / lex2.get_val();
	return (int)lex1.get_val() / (int)lex2.get_val();
}

ostream & operator << (ostream & s, Lex lx) {
	s << '(' << Scanner::LEXS[lx.get_type()] << ',';
	s << (lx.get_type() == LEX_FNUM ? lx.get_val() : (int)lx.get_val()) << ')';
	return s;
}



Scanner::Scanner(const char *filename)
{
	fp.open(filename);
	ST = H;
	gc();
}

Scanner::~Scanner()
{
	fp.close();
}

void Scanner::gc() {
	fp.get(c);
}

int Scanner::lookTW() {
	int i = 1;
	while (!TW[i].empty()) {
		if (!buf.compare(TW[i]))
			return i;
		++i;
	}
	return 0;
}

int Scanner::lookTD() {
	int i = 1;
	while (!TD[i].empty()) {
		if (!buf.compare(TD[i]))
			return i;
		++i;
	}
	return 0;
}

int Table_ident::put(Ident id) {
	for (size_t i = 0; i < TID.var.size(); i++)
		if (!id.name.compare(TID.var[i].name))
			return i;
	TID.var.push_back(id);
	return TID.var.size() - 1;
}

Lex Scanner::gl()
{
	int j, f = 0;
	ST = H;
	buf.clear();
	do {
		switch (ST) {
		case H:
			if (c == ' ' || c == '\t' || c == '\r') {
				gc();
				continue;
			}
			else if (isalpha(c))
				ST = IDENT;
			else if (isdigit(c))
				ST = NUM;
			else
				ST = DELIM;
			break;
		case IDENT:
			if (isalpha(c) || isdigit(c)) {
				buf.push_back(c);
				gc();
			}
			else {
				if ((j = lookTW()) != 0) {
					return Lex(tw[j], j);
				}
				else {
					Ident id(buf);
					j = TID.put(id);
					return Lex(LEX_ID, j);
				}
			}
			break;
		case NUM:
			if (isdigit(c)) {
				buf.push_back(c);
				gc();
			}
			else if (c == '.') {
				f = 1;
				buf.push_back(c);
				gc();
			}
			else if (f) 
				return Lex(stof(buf));
			else
				return Lex(stoi(buf));
			break;
		case DELIM:
			buf.push_back(c);
			if ((j = lookTD()) != 0) {
				gc();
				return Lex(td[j], j);
			}
			else
				throw c;
			break;
		}
	} while (1);
	return Lex();
}

void Table_ident::print() {
	cout << endl;
	for (size_t i = 0; i < TID.var.size(); i++) 
		cout << i << " : " << TID.var[i].name << endl;
}

