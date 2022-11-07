// clang-format off
#include <stdio.h> //for print f
#include <gmp.h> //for gmp library
// clang-format on
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
#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv)
{
	//make variables
	uint64_t bits = 1024;
	uint64_t iters = 50;
	time_t def_seed = time(NULL);
	uint64_t seed = def_seed;
	int v = 0;
	char pubfilename[] = "rsa.pub";
	char privfilename[] = "rsa.priv";
	char * pub = &pubfilename[0];
	char * priv = &privfilename[0];
	char * newpriv = NULL;
	char * newpub = NULL;
	int size;
	//for checking whether or not to clear arrays
	int pbclear;
	int pvclear;
	
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
				break;
			case 'i':
				iters = strtoul(optarg, NULL, 10);
				break;
			case 's':
				seed = strtoul(optarg, NULL, 10);
				break;
			case 'v':
				v = 1;
				break; 
			case 'h':
				fprintf(stderr, "./keygen generates a public / private key pair, placing the keys into the public and private key files as specified below. The keys have a modulus (n) whose length is specified in the program options.\n    -s <seed>   : Use <seed> as the random number seed. Default: time()\n    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n    -v          : Enable verbose output.\n    -h          : Display program synopsis and usage.\n");
				return 0;
			case 'd':
				size = sizeof(optarg);
				newpriv = calloc(size, sizeof(char));
				priv = strcpy(newpriv, optarg);
				pvclear = 1;
				break;
			case 'n':
				size = sizeof(optarg);
				newpub = calloc(size, sizeof(char));
				pub = strcpy(newpub, optarg);
				pbclear = 1;
				break;
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
	
	if(v == 1)
		{
		gmp_fprintf( stderr, "username: %s\nuser signature (%d bits): %Zd\np (%d bits): %Zd\nq (%d bits): %Zd\nn - modulus (%d bits): %Zd\ne - public exponent (%d bits): %Zd\nd - private exponent (%d bits): %Zd\n", username, mpz_sizeinbase(m,2), m, mpz_sizeinbase(p,2), p, mpz_sizeinbase(q,2), q, mpz_sizeinbase(n,2), n, mpz_sizeinbase(e,2), e, mpz_sizeinbase(d,2), d);
		}

	fclose(pbkey);
	fclose(pvkey);
	randstate_clear();
	if(pvclear == 1)
		{free(newpriv);}
	if(pbclear == 1)
		{free(newpub);}
	mpz_clear(p); mpz_clear(q); mpz_clear(n);
	mpz_clear(e); mpz_clear(d); mpz_clear(s);
	mpz_clear(m);
	return 0;
}
