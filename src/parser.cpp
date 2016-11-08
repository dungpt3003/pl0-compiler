#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
int parse_count = 0;
TokenType token;

static char *syntaxerrors[] =
{
    [1] = "Missing comma",
    [2] = "Missing period",
    [3] = "Missing semicolon",
    [4] = "Missing program name",
    [5] = "Missing keyword PROGRAM",
    [6] = "Missing bracket",
    [7] = "Missing parenthesis",
    [8] = "Syntax error in condition",
    [9] = "Missing token ASSIGN"
};

void nextToken(){
    token = tokenList[parse_count++];
}

void parseError(int err_num){
    fprintf(outfile, syntaxerrors[err_num]);
}

void factor(){
    if (token == NUMBER)
        nextToken();
    else if (token == IDENT){
        nextToken();
        if (token == LBRACK){
            nextToken();
            expression();
            if (token == RBRACK)
                nextToken();
            else
                parserError(6);
        }
    }
    else if (token == LPARENT){
        nextToken();
        expression();
        if (token == RPARENT)
            nextToken();
        else
            parserError(7);
    }
}

void term(){
    factor();
    while(token == TIMES || token == SLASH || token == PERCENT){
        nextToken();
        factor();
    }
}

void expression(){
    if (token == PLUS || token == MINUS)
        nextToken();
    term();
    if (token == PLUS || token == MINUS){
        nextToken();
        term();
    }
}

void program(){
    nextToken();
    if (token == PROGRAM){
        nextToken();
        if (token == IDENT){
            nextToken();
            if (token == SEMICOLON){
                nextToken();
                block();
                if (token == PERIOD)
                    fprintf(outfile, "The program is successfully compiled");
                else parseError(2);
            } else parseError(3);
        } else parseError(4);
    } else parseError(5);
}
