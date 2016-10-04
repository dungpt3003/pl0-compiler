#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pl0.h"

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
        	if(strcmp(ident, word[i]) == 0){
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
		do{
			number_ident = number_ident * 10 + current_character - '0';
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

	printToken();
}

void show_usage(char* program_name){
    printf("Usage: %s", program_name);
    printf(" input_file output_file\n");
    printf("Note: input_file is compulsory, output_file is optional (default: result.txt)\n");
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
    fclose(infile);
    fclose(outfile);
    return 0;
}
