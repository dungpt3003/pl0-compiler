#include <stdio.h>
#include <string.h>

#ifndef PLO_H_
#define PL0_H_
#define MAX_IDENT_LEN 10
#define MAX_PROGRAM_TOKEN 10000

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
TokenType tokenList[MAX_PROGRAM_TOKEN];
int number_ident;
char ident[MAX_IDENT_LEN + 1];
char ident_value[MAX_IDENT_LEN + 1];
bool is_keyword;
bool is_lex_error = false;
int token_count = 0;
int i, j, k;

// Keyword
TokenType keyword[] = {BEGIN, CALL, CONST, DO, ELSE, END, FOR, IF, ODD, PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE};
string word[] = {"BEGIN", "CALL", "CONST", "DO", "ELSE", "END", "FOR", "IF", "ODD", "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE"};

// Token
TokenType all_token[] = {IDENT, NUMBER, PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GTR, GEQ, LPARENT,
						RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON, ASSIGN, PERCENT};
string token_word[] = {"IDENT", "NUMBER", "PLUS", "MINUS", "TIMES", "SLASH", "EQU", "NEQ", "LSS", "LEQ", "GTR", "GEQ", "LPARENT",
						"RPARENT", "LBRACK", "RBRACK", "PERIOD", "COMMA", "SEMICOLON", "ASSIGN", "PERCENT"};

#endif
