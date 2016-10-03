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

char getCh(){
    current_character = fgetc(infile);
}


int main(int argc, char** argv){
    if ((infile = fopen("program.txt", "r")) == NULL){
        printf("Error when reading input file\n");
        exit(0);
    }
    if ((outfile = fopen("result.txt", "w")) == NULL){
        printf("Error when writing to output file\n");
        exit(0);
    }
    current_character = ' ';
    while (!feof(infile)){
        getCh();
        fprintf(outfile, "%c", current_character);
    }
    return 0;
}
