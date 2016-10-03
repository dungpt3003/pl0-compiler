#include <stdio.h>
#include <string.h>

#ifndef PLO_H_
#define PL0_H_
#define MAX_IDENT_LEN 10

typedef enum {
	NONE = 0, IDENT, NUMBER, BEGIN, CALL, CONST, DO, ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE, PLUS, MINUS, TIMES, SLASH, EQU,
	NEQ, LSS, LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA,
	SEMICOLON, ASSIGN, PERCENT
} TokenType;

typedef char string[MAX_IDENT_LEN + 1];

FILE* infile, *outfile;
char current_character;
TokenType current_token;
int number_ident;
char Ident[MAX_IDENT_LEN + 1];

// Keyword
TokenType keyword[] = {BEGIN, CALL, CONST, DO, ELSE, END, FOR, IF, ODD, PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE};
string word[] = {"BEGIN", "CALL", "CONST", "DO", "ELSE", "END", "FOR", "IF", "ODD", "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE"};

// Token
TokenType alltoken[] = {IDENT, NUMBER, PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GTR, GEQ, LPARENT,
						RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON, ASSIGN, PERCENT};
string tokenword[] = {"IDENT", "NUMBER", "PLUS", "MINUS", "TIMES", "SLASH", "EQU", "NEQ", "LSS", "LEQ", "GTR", "GEQ", "LPARENT",
						"RPARENT", "LBRACK", "RBRACK", "PERIOD", "COMMA", "SEMICOLON", "ASSIGN", "PERCENT"};

#endif
