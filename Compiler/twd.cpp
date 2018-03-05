#include "lexical.h"

type_lex Scanner::td[] = {
	LEX_NULL,
	LEX_ASSIGN,
	LEX_PLUS,
	LEX_MINUS,
	LEX_MUL,
	LEX_DIV,
	LEX_LPAREN,
	LEX_RPAREN,
	LEX_NLINE,
	LEX_COLON,
	LEX_COMA,
	LEX_LSQR,
	LEX_RSQR,
	LEX_SG,
	LEX_SL,
	LEX_SGE,
	LEX_SLE,
	LEX_SEQ,
	LEX_SNQ,
	LEX_FIN,
	LEX_NULL
};

type_lex Scanner::tw[] = {
	LEX_NULL,
	LEX_INT,
	LEX_FLOAT,
	LEX_CHAR,
	LEX_BOOL,
	LEX_TRUE,
	LEX_FALSE,
	LEX_STR,
	LEX_INPUT,
	LEX_PRINT,
	LEX_IF,
	LEX_ELSE,
	LEX_WHILE,
	LEX_AND,
	LEX_OR,
	LEX_NOT,
	LEX_NULL
};

const string Scanner::TD[] = {
	"",
	"=",
	"+",
	"-",
	"*",
	"/",
	"(",
	")",
	"\n",
	":",
	",",
	"[",
	"]",
	">",
	"<",
	">=",
	"<=",
	"==",
	"!=",
	"$",
	""
};

const string Scanner::TW[] = {
	"",
	"int",
	"float",
	"char",
	"bool",
	"true",
	"false",
	"str",
	"input",
	"print",
	"if",
	"else",
	"while",
	"and",
	"or",
	"not",
	""
};

const string Scanner::LEXS[] = {
	"LEX_NULL",
	"LEX_ASSIGN",
	"LEX_INT",
	"LEX_FLOAT",
	"LEX_STR",
	"LEX_CHAR",
	"LEX_BOOL",
	"LEX_TRUE",
	"LEX_FALSE",
	"LEX_FNUM",
	"LEX_INUM",
	"LEX_ID",
	"LEX_INPUT",
	"LEX_PRINT",
	"LEX_PLUS",
	"LEX_MINUS",
	"LEX_MUL",
	"LEX_DIV",
	"LEX_LPAREN", // )
	"LEX_RPAREN", // )
	"LEX_LSQR", // [
	"LEX_RSQR", // ]
	"LEX_IF",
	"LEX_ELSE",
	"LEX_WHILE",
	"LEX_COLON",
	"LEX_COMA",
	"LEX_NLINE",
	"LEX_AND",
	"LEX_OR",
	"LEX_NOT",
	"LEX_SEQ", // ==
	"LEX_SNQ", // !=
	"LEX_SG", // >
	"LEX_SL", // <
	"LEX_SGE", // >=
	"LEX_SLE", // <=
	"LEX_FIN",
	"POLIZ_GO",
	"POLIZ_FGO",
	"POLIZ_LABEL",
	"POLIZ_ADDRESS",
	""
};