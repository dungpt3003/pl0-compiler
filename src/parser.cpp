#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int parse_count = 0;
TokenType token;

void expression();
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
    [9] = "Missing ASSIGN (:=) ",
    [10] = "Missing fuction/procedure name",
    [11] = "Missing keyword END",
    [12] = "Missing keyword THEN",
    [13] = "Missing keyword DO"
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
                parseError(6);
        }
    }
    else if (token == LPARENT){
        nextToken();
        expression();
        if (token == RPARENT)
            nextToken();
        else
            parseError(7);
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


void condition(){
    expression();
    if (token == EQU || token == NEQ || token == LSS || token == LEQ || token == GTR || token == GEQ){
        nextToken();
        expression();
    }
    else
        parseError(8);
}

void statement(){
    // Branch 1: assign variables
    if (token == IDENT){
        nextToken();
        // For array variable
        if (token == LBRACK){
            nextToken();
            expression();
            if (token == RBRACK)
                nextToken();
            else
                parseError(6);
        }
        if (token == ASSIGN){
            nextToken();
            expression();
        } else
            parseError(9);
    }
    // Branch 2: Call procedure
    else if (token == CALL){
        nextToken();
        if (token == IDENT){
            if (token == LPARENT){
                nextToken();
                expression();
                while (token == COMMA){
                    nextToken();
                    expression();
                }
                if (token == RPARENT)
                    nextToken();
                else
                    parseError(7);
            }
        } else parseError(10);
    }
    // Branch 3: Begin - end block
    else if (token == BEGIN){
        nextToken();
        statement();
        while (token == SEMICOLON){
            nextToken();
            statement();
        }
        if (token == END)
            nextToken();
        else
            parseError(11);
    }

    // Branch 4: condition
    else if (token == IF){
        nextToken();
        condition();
        if (token == THEN){
            nextToken();
            statement();
            if (token == ELSE){
                nextToken();
                statement();
            }
        }
        else
            parseError(12);
    }

    // Branch 5: while loop
    else if (token == WHILE){
        nextToken();
        condition();
        if (token == DO){
            nextToken();
            statement();
        }
        else
            parseError(13);
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
