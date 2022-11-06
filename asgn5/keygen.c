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
#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv)
{
	//make variables
	uint64_t bits = 1024;
	uint64_t iters = 50;
	time_t def_seed = time(NULL);
	uint64_t seed = def_seed;
	//int v = 0;
	char pubfilename[] = "rsa.txt";
	char privfilename[] = "rsa.priv";
	char * pub = &pubfilename[0];
	char * priv = &privfilename[0];
	int size;
	
	int opt = 0;
	//mpz_t variables
	mpz_t p; mpz_init(p);
	mpz_t q; mpz_init(q);
	mpz_t n; mpz_init(n);
	mpz_t e; mpz_init(e);
	mpz_t d; mpz_init(d);
	mpz_t s; mpz_init(s);
	mpz_t m; mpz_init(m);
	//parse arguments
	while ((opt = getopt(argc, argv, OPTIONS)) != -1)
		{
		switch(opt)
			{
			//if its p, set p param to the argument 
			case 'b':
				bits = strtoul(optarg, NULL, 10);
			case 'i':
				iters = strtoul(optarg, NULL, 10);
			case 's':
				seed = strtoul(optarg, NULL, 10);
			/*case 'v':
				v = 1; */
			case 'h':
				printf("TODO: print help to stderror.\n");
				return 0;
			case 'd':
				size = sizeof(optarg);
				char *newpriv = calloc(size, sizeof(char));
				priv = strcpy(newpriv, optarg);
			case 'n':
				size = sizeof(optarg);
				char *newpub = calloc(size, sizeof(char));
				pub = strcpy(newpub, optarg);
			}
		}
	FILE *pbkey = fopen(pub, "w");
	FILE *pvkey = fopen(priv, "w");
	
	int filenum = fileno(pvkey);
	fchmod(filenum, 0600);

	randstate_init(seed);
	
	rsa_make_pub(p, q, n, e, bits, iters);
	rsa_make_priv(d, e, p, q);
	
	char *username = getenv("USERNAME");
	mpz_set_str(m, username, 62);
	rsa_sign(s, m, d, n);
	
	rsa_write_pub(n, e, s, username, pbkey);
	rsa_write_priv(n, d, pvkey);
	
	//verbose stuff

	fclose(pbkey);
	fclose(pvkey);
	randstate_clear();
	//free(newpriv);
	//free(newpub);
	mpz_clear(p); mpz_clear(q); mpz_clear(n);
	mpz_clear(e); mpz_clear(d); mpz_clear(s);
	mpz_clear(m);
}
