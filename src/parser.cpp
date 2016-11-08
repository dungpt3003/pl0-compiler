#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int parse_count = 0;
TokenType token;

void expression(void);
void block(void);
static char *syntaxerrors[] =
{
    [1] = "Missing comma\n",
    [2] = "Missing period\n",
    [3] = "Missing semicolon\n",
    [4] = "Missing program name\n",
    [5] = "Missing keyword PROGRAM\n",
    [6] = "Missing bracket\n",
    [7] = "Missing parenthesis\n",
    [8] = "Syntax error in condition\n",
    [9] = "Missing ASSIGN (:=)\n",
    [10] = "Missing fuction/procedure name\n",
    [11] = "Missing keyword END\n",
    [12] = "Missing keyword THEN\n",
    [13] = "Missing keyword DO\n",
    [14] = "Missing variable name\n",
    [15] = "Missing keyword TO\n",
    [16] = "Missing EQU (=)\n",
    [17] = "Invalid constant declaration: Constant must be a number\n",
    [18] = "Missing number of element of array\n"
};

void printOneToken(TokenType print_token){
    bool is_true = false;
    for (k = 0; k < 21; k++)
        if (print_token == all_token[k]){
            printf("%d %s\n", parse_count, token_word[k]);
            is_true = true;
        }
    for (k = 0; k < 15; k++)
         if (print_token == keyword[k]){
             printf(" %d %s\n", parse_count, word[k]);
             is_true = true;
         }
    if (!is_true)
        printf("Can't find the token\n");
}

void nextToken(){
    token = tokenList[parse_count++];
    printOneToken(token);
}


void parseError(int err_num){
    fprintf(outfile, syntaxerrors[err_num]);
    // Exit on first error
    exit(0);
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
    if (token == ODD){
        nextToken();
        expression();
    }
    else{
        expression();
        if (token == EQU || token == NEQ || token == LSS || token == LEQ || token == GTR || token == GEQ){
            nextToken();
            expression();
        }
        else
            parseError(8);
    }
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
            else nextToken();
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

    // Branch 6: for loop
    else if (token == FOR){
        nextToken();
        if (token == IDENT){
            nextToken();
            if (token == ASSIGN){
                nextToken();
                expression();
            }
            else
                parseError(9);

            if (token == TO){
                nextToken();
                expression();
            }
            else
                parseError(15);

            if (token == DO){
                nextToken();
                statement();
            }
            else
                parseError(13);
        }
        else
            parseError(14);
    }
}


void constant(){
    if (token == IDENT){
        nextToken();
        if (token == EQU){
            nextToken();
            if (token == NUMBER){
                nextToken();
                while (token == COMMA){
                    nextToken();
                    constant();
                }
                if (token == SEMICOLON){
                    nextToken();
                    block();
                }
                else
                    parseError(3);
            }
            else
                parseError(17);
        }
        else
            parseError(16);
    }
    else
        parseError(14);
}

void variable(){
    if (token == IDENT){
        nextToken();
        // For array variable
        if (token == LBRACK){
            nextToken();
            if (token == NUMBER){
                nextToken();
                if (token == RBRACK)
                    nextToken();
                else
                    parseError(6);
                if (token == SEMICOLON){
                    nextToken();
                    block();
                }
                else
                    parseError(3);
            }
            else
                parseError(18);
        }
        
        while (token == COMMA){
            nextToken();
            variable();
        }
    }
    else
        parseError(14);

}

void proVariable(){
    while (token != RPARENT){
        if (token == VAR)
            nextToken();
        if (token == IDENT){
            nextToken();
            while (token == SEMICOLON){
                nextToken();
                proVariable();
            }
        }
        else parseError(14);
    }
}

void block(){
    // Branch 1: Declare constants
    while (token == CONST){
        nextToken();
        constant();
    }

    // Branch 2: Declare variables
    while (token == VAR){
        nextToken();
        variable();
    }

    // Branch 3: Procedure
    while (token == PROCEDURE){
        nextToken();
        if (token == IDENT){
            nextToken();
            if (token == LPARENT){
                nextToken();
                proVariable();
                if (token == RPARENT)
                    nextToken();
                else
                    parseError(7);
            }

            if (token == SEMICOLON){
                block();
                if (token == SEMICOLON)
                    nextToken();
                else
                    parseError(3);
            }
            else
                parseError(3);
        }
        else
            parseError(10);
    }

    // Branch 4: Begin - end
    if (token == BEGIN){
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
