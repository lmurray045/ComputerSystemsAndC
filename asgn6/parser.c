#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h"
#define MAX_PARSER_LINE_LENGTH 1000

//creates a parser function for reading and parsing through file input
struct Parser {
	FILE *f;
	char current_line[MAX_PARSER_LINE_LENGTH + 1];
	uint32_t line_offset;
};

//parser creator
Parser *parser_create(FILE *f){
	Parser *par = (Parser *)malloc(sizeof(Parser));
	par->f = f;
	return par;
}

//parser delete
void parser_delete(Parser **p){
	free(*p);
}

//parser next word
bool next_word(Parser *p, char *word){
	int chnum = -1;
	while(isalnum(chnum) == 0){
		 chnum = fgetc(p->f);
		 printf("chnum = %d\n", chnum);
		 printf("is alpha num: %d\n", isalnum(chnum));
		 if(isalnum(chnum) != 0){
		 	printf("its a word\n");
		 	chnum = tolower(chnum);
		 	*word = chnum;
		 }
		 else if(chnum == EOF){
		 	return false;
		 }
	}
	int i;
	chnum = fgetc(p->f);
	for(i = 1; isalnum(chnum) != 0; i++){
		printf("letter: %d\n", chnum);
		chnum = tolower(chnum);
		*(word+i) = chnum;
		chnum = fgetc(p->f);
	}
	*(word+i) = '\0';
	return true;
}

int main(void){
	FILE *fp = fopen("Parsefile.txt", "r");
	Parser *p = parser_create(fp);
	char word[100];
	char * wp = &word[0];
	next_word(p, wp);
	printf("Parsed Word: %s\n", wp);
	next_word(p, wp);
	printf("Parsed Word: %s\n", wp);
	next_word(p, wp);
	printf("Parsed Word: %s\n", wp);
	next_word(p, wp);
	printf("Parsed Word: %s\n", wp);
	fclose(fp);
	parser_delete(&p);
	return 0;
}
