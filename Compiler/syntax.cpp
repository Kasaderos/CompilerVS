﻿#include "lexical.h"
#include "syntax.h"

extern Table_ident TID;

template <class T, int max_size > 
Stack <T, max_size>::Stack() {
	s = new T[size = max_size];
	top = 0;
}

template <class T, int max_size >
Stack <T, max_size>::~Stack() {
	delete[] s;
}

template <class T, int max_size >
void Stack <T, max_size >::reset() { top = 0; }

template <class T, int max_size >
bool Stack <T, max_size >::is_empty() { return top == 0; }

template <class T, int max_size >
bool Stack <T, max_size >::is_full() { return top == max_size; }

template <class T, int max_size >
void Stack <T, max_size >::print() {
	for (int i = 0; i < top; i++)
		cout << i << " " << s[i] << endl;
}

template <class T, int max_size >
void Stack <T, max_size >::push(T i)
{
	if (!is_full()) {
		s[top] = i;
		++top;
	}
	else
		throw "Stack_is_full";
}

template <class T, int max_size >
T Stack <T, max_size >::pop()
{
	if (!is_empty())
	{
		--top;
		return s[top];
	}
	else
		throw "Stack_is_empty";
}

Poliz::Poliz(int max_size) {
	p = new Lex[size = max_size];
	pos = 0;
}

Poliz::~Poliz() {
	delete[] p;
}
void Poliz::put_lex(Lex l) { p[pos] = l; ++pos; }
void Poliz::put_lex(Lex l, int place) { p[place] = l; }
void Poliz::blank() { ++pos; }
int Poliz::get_pos() { return pos; };

Lex & Poliz::operator[] (int index)
{
	if (index > size)
		throw "POLIZ:out of array";
	else
		if (index > pos)
			throw "POLIZ:indefinite element of array";
		else
			return p[index];
};

void Poliz::print() {
	for (int i = 0; i < pos; i++)
		cout << p[i];
}

Parser::Parser(const char * program) : scan(program), prog(1000) {}

void Parser::deleteNLINE() {
	do {
		get_lex();
	} while (curr_t == LEX_NLINE);
	//cout << "deleteNLINE: " << Scanner::LEXS[curr_t] << endl;
}
void Parser::get_lex() {
	curr_lex = scan.get_lex();
	curr_t = curr_lex.get_type();
	curr_v = curr_lex.get_val();
	//cout << curr_lex << endl;
}
void Parser::analyze() {
	cout << "starting analyze: " << endl;
	Prog();
	prog.print();
	cout << endl << "Parser success" << endl;
}

void Parser::Prog() {
	//cout << "Prog" << endl;
	deleteNLINE();
	Dcls();
	Stmts();
	if (curr_t != LEX_FIN)
		throw curr_lex;
}

void Parser::Dcls() {
	//cout << "Dcls" << endl;
	st_int.reset();
	while (1) {
		Del();
		deleteNLINE();
		if (curr_t == LEX_ID || curr_t == LEX_PRINT || curr_t == LEX_FIN)
			break;
	};
}

void Parser::Del() {
	//cout << "Del" << endl;
	if (curr_t != LEX_FLOAT && curr_t != LEX_INT)
		throw curr_lex;
	type_var = curr_t; // declaration designed by stack
	do {
		get_lex();
		if (curr_t != LEX_ID)
			throw curr_lex;
		st_int.push(curr_v);
		get_lex();
	} while (curr_t == LEX_COMMA);
	dec();						 				
	if (curr_t != LEX_NLINE)
		throw curr_lex;
}

void Parser::Stmts() {
	//cout << "Stmts" << endl;
	while (1) {
		Stmt();
		if (curr_t == LEX_FIN)
			return;
		deleteNLINE();


	}
}

void Parser::Stmt() {
	//cout << "Stmt" << endl;
	if (curr_t == LEX_FIN) {
		return;
	}
	else if (curr_t == LEX_ID) {
		check_id();
		prog.put_lex(Lex(POLIZ_ADDRESS, curr_v));
		get_lex();
		if (curr_t != LEX_ASSIGN)
			throw curr_lex;
		Val();
		Expr();
		prog.put_lex(Lex(LEX_ASSIGN));
	}
	else if (curr_t == LEX_PRINT) {
		get_lex();
		if (curr_t != LEX_ID)
			throw curr_lex;
		check_id();
		prog.put_lex(curr_lex);
		prog.put_lex(Lex(LEX_PRINT));
		get_lex();
		if (curr_t != LEX_NLINE)
			throw curr_lex;
	}
	else
		throw curr_lex;
}

void Parser::Val() {
	//cout << "Val" << endl;
	get_lex();
	if (curr_t == LEX_ID) {
		check_id();
		prog.put_lex(Lex(LEX_ID, curr_v));
	}
	else if (curr_t == LEX_FNUM || curr_t == LEX_INUM) {
		st_lex.push(curr_lex);
		prog.put_lex(curr_lex);
	}
	else if (curr_t == LEX_LPAREN) {
		Val();
		Expr();
		if (curr_t != LEX_RPAREN)
			throw curr_lex;
	}else
		throw curr_lex;
}

void Parser::Expr() {
	//cout << "Expr" << endl;
	get_lex();
	while (curr_t != LEX_NLINE && curr_t != LEX_RPAREN) {
		if (curr_t != LEX_PLUS && curr_t != LEX_MINUS
						&& curr_t != LEX_MUL && curr_t != LEX_DIV)
			throw curr_lex;
		st_lex.push(curr_lex);
		Val();
		check_op();
		get_lex();
	}
}

void Parser::dec()
{
	int i;
	while (!st_int.is_empty())
	{
		i = st_int.pop();
		if (TID.var[i].declare)
			throw "Redeclaration";
		else
		{
			TID.var[i].declare = true;
			TID.var[i].set_type(type_var); //type_var 
			cout << "declared : " << TID.var[i].name << endl;
		}
	}
	
}

void Parser::check_id()
{
	int c_val = (int)curr_v;
	if (TID.var[c_val].declare)
		st_lex.push(Lex(TID.var[c_val].get_type(), curr_v));
	else
		throw "Not declared";
}

void Parser::eq_type()
{
	Lex t1 = st_lex.pop();
	Lex t2 = st_lex.pop();
	if (t1.get_type() != t1.get_type()) throw "Wrong types are in =";
}

void Parser::check_op()
{
	Lex t1, t2, op;
	t2 = st_lex.pop();
	op = st_lex.pop();
	prog.put_lex(op);
	t1 = st_lex.pop();
	cout << "t2 op t1 : ";
	cout << Scanner::LEXS[t2.get_type()] << " ";
	cout << Scanner::LEXS[op.get_type()] << " ";
	cout << Scanner::LEXS[t1.get_type()] << endl;

	if (t1.get_type() != t2.get_type())
		st_lex.push(Lex(LEX_FLOAT));
	else if (t1.get_type() == t2.get_type())
		st_lex.push(t1);
	else
		throw "Wrong types are in operation";
}

void Executer::execute(Poliz & prog) {
	Stack< Lex, 100 > args;
	int i, index = 0;
	Lex lex1, lex2, lex3;
	int size = prog.get_pos();

	while (index < size) {
		args.print();
		cout << endl;
		curr_lex = prog[index];
		switch (curr_lex.get_type())
		{
		case LEX_INUM:
		case LEX_FNUM:
		case POLIZ_ADDRESS:
			args.push(curr_lex);
			break;
		case LEX_ID:
			i = (int)curr_lex.get_val();
			if (TID.var[i].assign) {
				args.push(curr_lex);
				break;
			}
			else
				throw "POLIZ: indefinite identifier";
		case LEX_PLUS:
			args.push(args.pop() + args.pop());
			break;
		case LEX_MINUS:
			lex1 = args.pop();
			args.push(args.pop() - lex1);
			break;
		case LEX_MUL:
			args.push(args.pop() * args.pop());
			break;
		case LEX_DIV:
			lex1 = args.pop();
			args.push(args.pop() / lex1);
			break;
		case LEX_ASSIGN:
			lex1 = args.pop();
			//cout << "lvalue : " << lex1.v_lex.d << endl;
			lex2 = args.pop();
			lex3 = to_const(lex1);
			i = (int)lex2.get_val();
			if (lex3.get_type() == LEX_FNUM && TID.var[i].get_type() == LEX_INT)
				throw "impilcit float to int";
			//cout << "rvalue : " << lex3.v_lex.d << endl;
			TID.var[i].set_val(lex3.get_val());
			TID.var[i].assign = true;
			break;
		case LEX_PRINT:
			lex1 = args.pop();
			lex1 = to_const(lex1);
			if (lex1.get_type() == LEX_INUM)
				cout << (int)lex1.get_val() << endl;
			else
				cout << lex1.get_val() << endl;
			break;
		default:
			throw "POLIZ: unexpected elem";
		}
		++index;
	}
	cout << "Finish of executing!!!" << endl;
}


void Interpretator::interpretation()
{
	pars.analyze();
	cout << "Start execute: " << endl;
	E.execute(pars.prog);
}

