#include <stdio.h> //for print f
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#include <gmp.h> //for gmp library
#include <stdbool.h> //for booleans
#include <stdint.h> //for int types 
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv)
{
	int v = 0;
	//make default in and out files
	char infile[] = "stdin";
	char outfile[] = "stdout";
	char * in = &infile[0];
	char * out = &outfile[0];
	char * newin = NULL;
	char * newout = NULL;
	//make default pub key file
	char keyfile[] = "rsa.pub";
	char * key = &keyfile[0];
	char * newkey = NULL;
	//for checking whether or not to clear arrays
	int inclear;
	int outclear;
	int keyclear;
	int size;
	
	int opt = 0;
	//mpz_t variables
	mpz_t n; mpz_init(n);
	mpz_t e; mpz_init(e);
	mpz_t s; mpz_init(s);
	mpz_t expected; mpz_init(expected);
	//parse arguments
	while ((opt = getopt(argc, argv, OPTIONS)) != -1)
		{
		switch(opt)
			{
			//if its p, set p param to the argument 
			case 'i':
				size = sizeof(optarg);
				newin = calloc(size, sizeof(char));
				in = strcpy(newin, optarg);
				inclear = 1;
				break;
			case 'o':
				size = sizeof(optarg);
				newout = calloc(size, sizeof(char));
				out = strcpy(newout, optarg);
				outclear = 1;
				break;
			case 'n':
				size = sizeof(optarg);
				newkey = calloc(size, sizeof(char));
				key = strcpy(newkey, optarg);
				keyclear = 1;
				break;
			case 'v':
				v = 1;
				break; 
			case 'h':
				fprintf(stderr, "./encrypt-dist generates encoded cyphertext, reading a message from the input and storing in in the output as specified below. The cyphertext is generated based off of a public key, which is read via the input specified below.\n    -i <input>   : read the message to be encrypted from <input>. Default: stdin\n    -o <output>   : store the generated cyphertext into <output>. Default: stdout\n    -n <public key file>  : gather the public key information from <public key file>. Default: 'rsa.pub'\n    -v          : Enable verbose output.\n    -h          : Display program synopsis and usage.\n");
				return 0;
			}
		}
	FILE * kfp  = fopen(key, "r");
	char username[10];
	rsa_read_pub(n, e, s, username, kfp);
	if(v == 1)
		{
		gmp_fprintf(stderr, "username: %s\nuser signature (%d bits): %Zd\nn - modulus (%d bits): %Zd\ne - public exponent (%d bits): %Zd\n", username, mpz_sizeinbase(s,2), s, mpz_sizeinbase(n,2), n, mpz_sizeinbase(e,2), e);
		}
	mpz_set_str(expected, username, 62);
	if(rsa_verify(expected, s, e, n) != true)
		{
		fprintf(stderr, "verify failed\n");
		}
	FILE * ifp = NULL;
	FILE * ofp = NULL;
	if(inclear == 0)
		{
		ifp = stdin;
		}
	else
		{
		ifp = fopen(in, "r");
		}
	if(outclear == 0)
		{
		ofp = stdout;
		}
	else
		{
		ofp = fopen(out, "w");
		}
	rsa_encrypt_file(ifp, ofp, n, e);
	//close out program
	fclose(kfp);
	fclose(ifp);
	fclose(ofp);
	if(inclear == 1)
		{free(newin);}
	if(outclear == 1)
		{free(newout);}
	if(keyclear == 1)
		{free(newkey);}
	mpz_clear(n);
	mpz_clear(e);
	mpz_clear(s);
	mpz_clear(expected);
	return 0;
}
