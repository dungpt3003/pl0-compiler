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

// Print tokens and lexemes
void printToken(){
	if (Token == IDENT){
		is_keyword = false;
        i = 0;
        while (word[i] != NULL){
        	if(strcmp(ident, word[i]) == 0){
        		fprintf(outfile, "%s\n", word[i]);
				is_keyword = true;
				break;
			}
            i++;
		}
		if (is_keyword == false){
			fprintf(outfile, "IDENT(%s)\n", ident);
		}
	}
	else if (current_token == NUMBER)
		fprintf(outfile, "NUMBER(%d)\n", number_ident);
	else {
        k = 0;
		while(all_token[k] != NULL)){
			if (current_token == all_token[k])
				fprintf(outfile, "%s\n", token_word[k]);
            k++;
		}
	}

}

char getCh(){
    current_character = fgetc(infile);
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
        getCh();
        fprintf(outfile, "%c", current_character);
    }
    return 0;
}
