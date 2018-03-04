#include <string>
#include "lexical.h"
using namespace std;

extern Table_ident TID;

Ident::Ident() : val(""), declare(false), assign(false) {}

Ident::Ident(const string str) : name(str), val(""), declare(false), assign(false) {}

int Table_ident::put(Ident id) {
	for (size_t i = 0; i < TID.var.size(); i++)
		if (!id.name.compare(TID.var[i].name))
			return i;
	TID.var.push_back(id);
	return TID.var.size() - 1;
}
const string Scanner::TWD[] = { "", "=", "int", "float", "print", "+", "-", "\n", "$" };

const string Scanner::LEXS[] = {
	"LEX_NULL", // 0   
	"LEX_ASSIGN", // 1
	"LEX_INT", // 2
	"LEX_FLOAT", "LEX_PRINT",  // 3, 4, 
	"LEX_PLUS", "LEX_MINUS", "LEX_NLINE", // 5, 6, 7
	"LEX_FIN", // 8
	"LEX_FNUM", "LEX_INUM", // 9, 10 
	"LEX_ID", // 11
	"POLIZ_ADDRESS", // 12
};
Lex::Lex() {
	t_lex = LEX_NULL;
	v_lex = "_";
}
Lex::Lex(type_lex t, string v) {
	t_lex = t;
	v_lex = v;
}

Lex::Lex(int i) {
	t_lex = LEX_INUM;
	v_lex = to_string(i);
}

Lex::Lex(double f) {
	t_lex = LEX_FNUM;
	v_lex = to_string(f);
}

Lex convert(const Lex & a) {
	if (a.t_lex == LEX_ID) {
		int i = atoi(a.v_lex.c_str());
		cout << "convert : ";
		cout << Scanner::LEXS[TID.var[i].type] << endl;
		if (TID.var[i].type == LEX_INT)
			return Lex(LEX_INUM, TID.var[i].val);
		if (TID.var[i].type == LEX_FLOAT)
			return Lex(LEX_FNUM, TID.var[i].val);
		else
			throw "error convert lex";
	}
	return a;
}

Lex operator + (const Lex & a, const Lex & b) {
	Lex lex1 = convert(a);
	Lex lex2 = convert(b);
	cout << Scanner::LEXS[lex1.t_lex] << endl;
	cout << Scanner::LEXS[lex2.t_lex] << endl;
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return atof(lex1.v_lex.c_str()) + atof(lex2.v_lex.c_str());
	return atoi(lex1.v_lex.c_str()) + atoi(lex2.v_lex.c_str());
}

/* Lex + Lex
Lex FNUM, INUM, ID

*/
Lex operator - (const Lex & a, const Lex & b) {
	Lex lex1 = convert(a);
	Lex lex2 = convert(b);
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return atof(lex1.v_lex.c_str()) - atof(lex2.v_lex.c_str());
	return atoi(lex1.v_lex.c_str()) - atoi(lex2.v_lex.c_str());
}
/*
Lex Lex::operator * (const Lex & a, const Lex & b){

}
Lex Lex::operator / (const Lex & a, const Lex & b){

}*/
ostream & operator << (ostream & s, Lex lx) {
	s << '(' << Scanner::LEXS[lx.t_lex] << ',' << lx.v_lex << ')';
	return s;
}

type_lex Scanner::types[] = {
	LEX_NULL, // 0   
	LEX_ASSIGN, // 1
	LEX_INT, // 2
	LEX_FLOAT, LEX_PRINT, // 3, 4, 
	LEX_PLUS, LEX_MINUS, LEX_NLINE, // 5, 6, 7
	LEX_FIN, // 8
	LEX_FNUM, LEX_INUM, // 9, 10
	LEX_ID, // 11
	POLIZ_ADDRESS, // 12
};

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

int Scanner::look() {
	for (int i = 0; i < NUM_WORDS; i++)
		if (!buf.compare(TWD[i]))
			return i;
	return 0;
}

Lex Scanner::get_lex()
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
				if ((j = look()) != 0) {
					return Lex(types[j], to_string(j));
				}
				else {
					Ident id(buf);
					j = TID.put(id);
					return Lex(LEX_ID, to_string(j));
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
				return Lex(LEX_FNUM, buf);
			else
				return Lex(LEX_INUM, buf);
			break;
		case DELIM:
			buf.push_back(c);
			if ((j = look()) != 0) {
				gc();
				return Lex(types[j], to_string(j));
			}
			else
				throw c;
			break;
		}
	} while (1);
	return Lex(LEX_NULL, "");
}
/*
d = atoi(buf.c_str()); // int(string)
//buf.clear();
}
else if (f) {
flt = d + atof(buf.c_str()) / pow(10, buf.size()); // ����� + ������� �����
return Lex(LEX_FNUM, to_string(flt));
}*/
