// clang-format off
#include <stdio.h> //for print f
#include <gmp.h> 
//clang-format on
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
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
	char infile[] = "NULL";
	char outfile[] = "NULL";
	char * in = &infile[0];
	char * out = &outfile[0];
	char * newin = NULL;
	char * newout = NULL;
	//make default pub key file
	char keyfile[] = "rsa.priv";
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
	mpz_t d; mpz_init(d);
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
				fprintf(stderr, "./decrypt-dist decodes cyphertext, reading the encrypted message from the input and storing it in the output as specified below. The message is decrypted based off of a private key, which is read via the input specified below.\n    -i <input>   : reads the cyphertext to decode from <input>. Default: stdin\n    -o <output>   : store the decrypted message into <output>. Default: stdout\n    -n <private key file>  : gather the private key information from <private key file>. Default: 'rsa.priv'\n    -v          : Enable verbose output.\n    -h          : Display program synopsis and usage.\n");
				return 0;
			}
		}
	FILE * kfp  = fopen(key, "r");
	rsa_read_priv(n, d, kfp);
	if(v == 1)
		{
		gmp_fprintf(stderr, "n - modulus (%d bits): %Zd\nd - private exponent (%d bits): %Zd\n", mpz_sizeinbase(n,2), n, mpz_sizeinbase(d,2), d);
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
	rsa_decrypt_file(ifp, ofp, n, d);
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
	mpz_clear(d);
	return 0;
}
