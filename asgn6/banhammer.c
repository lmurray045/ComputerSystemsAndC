#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include "node.h"
#include "ll.h"
#include "ht.h"
#include "bv.h"
#include "bf.h"
#include "parser.h"
#include "city.h"
#define OPTIONS "ht:f:sm"

int main(int argc, char **argv){
	int helpprint = 0;
	uint32_t htsize = 10000;
	uint32_t bfsize = pow(2, 19);
	bool mtf = false;
	int statprint = 0;
	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1)
		{
		switch(opt)
			{
			//if its p, set p param to the argument 
			case 'h':
				helpprint = 1;
				break;
			case 't':
				htsize = strtoul(optarg, NULL, 10);
				break;
			case 'f':
				bfsize = strtoul(optarg, NULL, 10);
				break;
			case 'm':
				mtf = true;
				break;
			case 's':
				statprint = 1;
				break;
			}
		}
	BloomFilter *bf = bf_create(bfsize);
	HashTable *ht = ht_create(htsize, mtf);
	FILE *bs = fopen("badspeak.txt", "r");
	Parser *badparse = parser_create(bs);
	//pointer for badspeak, which has no newspeak translation
	char *nullnewspeak = NULL;
	char wordbuf[1001];
	char *word = &wordbuf[0];
	printf("loop one\n");
	while(next_word(badparse, word) == true){
		bf_insert(bf, word);
		ht_insert(ht, word, nullnewspeak);
	}
	printf("loop one exited\n");
	fclose(bs);
	FILE *ns = fopen("newspeak.txt", "r");
	Parser *newparse = parser_create(ns);
	char newword[1000];
	char * new = &newword[0];
	printf("loop two\n");
	while(next_word(newparse, word) == true){
		next_word(newparse, new);
		bf_insert(bf, word);
		ht_insert(ht, word, new);
	}
	fclose(ns);
	printf("loop two exited\n");
	bf_print(bf);
	ht_print(ht);
	
	//so no errors
	printf("%d\n", helpprint);
	printf("%d\n", statprint);
	return 0;
}
