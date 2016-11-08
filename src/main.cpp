#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "pl0.h"
#include "parser.cpp"

int is_letter(char c){
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
       return 1;
    return 0;
}

int is_digit(char c){
    if(c >= '0' && c <= '9')
       return 1;
    return 0;
}


char getChar(){
    current_character = fgetc(infile);
}

// Print tokens and lexemes
void printToken(){
    if (current_token == IDENT){
    	is_keyword = false;
        for (i = 0; i < 15; i++){
        	if(strcasecmp(ident, word[i]) == 0){
        		fprintf(outfile, "%s\n", word[i]);
    			is_keyword = true;
    			break;
    		}
    	}
    	if (is_keyword == false){
    		fprintf(outfile, "IDENT(%s)\n", ident);
    	}
    }
    else if (current_token == NUMBER)
    	fprintf(outfile, "NUMBER(%d)\n", number_ident);
    else {
        for (k = 0; k < 21; k++){
    		if (current_token == all_token[k])
    			fprintf(outfile, "%s\n", token_word[k]);
    	}
    }

}


bool is_match(TokenType token_check){
   for (k = 0; k < 21; k++)
        if (token_check == all_token[k])
            return true;
    for (k = 0; k < 15; k++)
      if (token_check == keyword[k])
        return true;
    return false;
}
// Push token to tokenList
void pushToken(){
    if (is_match(current_token)){
      if (current_token == IDENT){
        is_keyword = false;
          for (i = 0; i < 15; i++){
            if(strcasecmp(ident, word[i]) == 0){
                tokenList[token_count++] = keyword[i];
            is_keyword = true;
            break;
          }
        }
        if (is_keyword == false){
          tokenList[token_count++] = IDENT;
        }
      }
      else {
          tokenList[token_count++] = current_token;
      }
   }
}

// Print lexical analyser error
void lexerror(char *err, ...){
  fprintf(outfile,"Lexical error: %s\n", err);
  exit(0);
}

//Receive one-character token
void getSingleToken(){
	switch(current_character){
    	case '+':
    		current_token = PLUS;
    		getChar();
    		break;
    	case '-':
    		current_token = MINUS;
    		getChar();
    		break;
    	case '*':
    		current_token = TIMES;
    		getChar();
    		break;
    	case '/':
    		current_token = SLASH;
    		getChar();
    		break;
    	case '%':
    		current_token = PERCENT;
    		getChar();
    		break;
    	case '(':
    		current_token = LPARENT;
    		getChar();
    		break;
    	case ')':
    		current_token = RPARENT;
    		getChar();
    		break;
    	case '[':
    		current_token = LBRACK;
    		getChar();
    		break;
    	case ']':
    		current_token = RBRACK;
    		getChar();
    		break;
    	case '.':
    		current_token = PERIOD;
    		getChar();
    		break;
    	case ',':
    		current_token = COMMA;
    		getChar();
    		break;
    	case ';':
    		current_token = SEMICOLON;
    		getChar();
    		break;
    	case '=':
    		current_token = EQU;
    		getChar();
    		break;
    	default:
    		current_token = NONE;
    		getChar();
	}
}

// Lexeme analyzer
void getToken(){
    // Remove empty character
    while (current_character == ' ') getChar();

    // Receive IDENT
    if (is_letter(current_character)){
    	current_token = IDENT;
        k = 0;
        do  {
            if (k < MAX_IDENT_LEN)
                ident_value[k++] = current_character;
            else
                lexerror("Too long ident, max ident length is 10");
            getChar();
        }
        while (is_letter(current_character) || is_digit(current_character));
        ident_value[k] = '\0';
        strcpy(ident, ident_value);
    }

    // Receive NUMBER
    else if(is_digit(current_character)){
    	current_token = NUMBER;
    	number_ident = 0;
      k = 0;
    	do{
        if (k++ < MAX_IDENT_LEN)
            number_ident = number_ident * 10 + current_character - '0';
        else
            lexerror("The number is too big, max number length is 10");
    		getChar();
    	} while(is_digit(current_character));

    }

    // Receive complex lexemes

    else if (current_character == '>'){
    	getChar();
    	if (current_character == '=')
    		current_token = GEQ;
    	else
    		current_token = GTR;
    	getChar();
    }
    else if (current_character == '<'){
    	getChar();
    	if (current_character == '=')
    		current_token = LEQ;
    	else if (current_character == '>')
    		current_token = NEQ;
    	else
    		current_token = LSS;
    	getChar();
    }
    else if (current_character == ':'){
    	getChar();
    	if (current_character == '=')
    		current_token = ASSIGN;
    	else
    		current_token = NONE;
    	getChar();
    }
    else getSingleToken();

    //printToken();
    pushToken();
}

void show_usage(char* program_name){
    printf("Usage: %s", program_name);
    printf(" input_file output_file\n");
    printf("Note: These parameters are compulsory, you can use either absolute or relative path\n");
}

int main(int argc, char** argv){

    if (argc < 3){
        show_usage(argv[0]);
        return 1;
    }
    if ((infile = fopen(argv[1], "r")) == NULL){
        printf("Error when reading input file\n");
        return 1;
    }
    if ((outfile = fopen(argv[2], "w")) == NULL){
        printf("Error when writing to output file\n");
        return 1;
    }
    current_character = ' ';
    while (!feof(infile)){
        getToken();
    }
    // for (i = 0; i < token_count; i++){
    //   for (k = 0; k < 21; k++)
    //     if (tokenList[i] == all_token[k]){
    //       fprintf(outfile, "%s\n", token_word[k]);
    //     }
    //     for (k = 0; k < 15; k++)
    //       if (tokenList[i] == keyword[k]){
    //         fprintf(outfile, "%s\n", word[k]);
    //       }
    //
    // }
    program();
    fclose(infile);
    fclose(outfile);
    return 0;
}
