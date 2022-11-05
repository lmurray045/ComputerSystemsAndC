#include <stdio.h> //for print f
#include "randstate.h"
#include "numtheory.h"
#include "randstate.h"
#include <gmp.h> //for gmp library
#include <stdbool.h> //for booleans
#include <stdint.h> //for int types 
#include <stdarg.h>
#include "stdlib.h"
#include <math.h>

//rsa make pub
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters)
{
	printf("beginning\n");
	//make p with random bits
	uint64_t bottom_range = nbits / 4;
	uint64_t top_range = ((2 * nbits) / 4) + 1;
	mpz_t pbt; mpz_init(pbt);
	mpz_t trange; mpz_init(trange); mpz_set_ui(trange, top_range);
	mpz_t brange; mpz_init(brange); mpz_set_ui(brange, bottom_range);
	mpz_urandomm(pbt, state, trange);
	printf("pbt: %lu\n", mpz_get_ui(pbt));
	mpz_add(pbt, pbt, brange);
	
	printf("check 1\n");
	uint64_t pnbits = mpz_get_ui(pbt);
	//make p prime number
	make_prime(p, pnbits, iters);
	printf("p bits: %lu\n", pnbits);
	//calculate q bits
	//calculate q
	uint64_t qnbits = nbits - pnbits;
	printf("qnbits: %lu\n", qnbits);
	
	printf("check 2\n");

	make_prime(q, qnbits, iters);
	printf("q calculated\n");
	//calculate lambda 
	//declare variables
	mpz_t qm1; mpz_init(qm1);
	mpz_t pm1; mpz_init(pm1);
	mpz_t lam; mpz_init(lam);
	mpz_t prod; mpz_init(prod);
	printf("variables made\n");
	//find q-1 and p-1
	mpz_sub_ui(qm1, q, 1);
	mpz_sub_ui(pm1, p, 1);
	mpz_mul(prod, qm1, pm1);
	printf("variables calculated\n");
	//find lambda
	gcd(lam, qm1, pm1);
	mpz_fdiv_q(lam, prod, lam);
	printf("check 3\n");
	//find e
	mpz_t test; mpz_init(test);
	uint64_t e_top = (3 * nbits) / 4;
	uint64_t e_bot = nbits / 2;
	mpz_urandomb(e, state, e_top);
	mpz_add_ui(e, e, e_bot);
	gcd(test, e, lam);
	printf("while loop\n");
	while(mpz_cmp_ui(test, 1) != 0)
		{
		mpz_urandomb(e, state, e_top);
		mpz_add_ui(e, e, e_bot);
		gcd(test, e, lam);
		}
	printf("exited while loop\n");
	mpz_mul(n, p, q);
	return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile)
{
	//const char str[] = "%zx\n";
	//const char * point = &str[0];
	gmp_fprintf(pbfile, "%Zx\n", n);
	gmp_fprintf(pbfile, "%Zx\n", e);
	gmp_fprintf(pbfile, "%Zx\n", s);
	fprintf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q)
{
	mpz_t pm1; mpz_init(pm1); mpz_sub_ui(pm1, p, 1);
	mpz_t qm1; mpz_init(qm1); mpz_sub_ui(qm1, q, 1);
	mpz_t lam; mpz_init(lam);
	mpz_t gc; mpz_init(gc);
	gcd(gc, pm1, qm1);
	mpz_mul(lam, pm1, qm1);
	mpz_fdiv_q(lam, lam, gc);
	mod_inverse(d, e, lam);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile)
{
	gmp_fprintf(pvfile, "%Zx\n", n);
	gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile)
{
	gmp_fscanf(pbfile, "%Zx\n", n);
	gmp_fscanf(pbfile, "%Zx\n", e);
	gmp_fscanf(pbfile, "%Zx\n", s);
	fscanf(pbfile, "%s\n", username);

}

int main(void)
{
randstate_init(1234567);

mpz_t p; mpz_init(p);
mpz_t q; mpz_init(q);
mpz_t n; mpz_init(n);
mpz_t e; mpz_init(e);
mpz_t d; mpz_init(d);
mpz_t s; mpz_init(s); mpz_set_ui(s, 12345);

mpz_t nt; mpz_init(nt);
mpz_t e2; mpz_init(e2);
mpz_t s2; mpz_init(s2); mpz_set_ui(s, 12345);
char username2[8];

uint64_t bits = 1024;
uint64_t iters = ( random() % 500 );

rsa_make_pub(p, q, n, e, bits, iters);
printf("p: %lu, q: %lu, n: %lu, e: %lu\n", mpz_get_ui(p),mpz_get_ui(q),mpz_get_ui(n),mpz_get_ui(e));

rsa_make_priv(d, e, p, q);
printf("d: %lu\n", mpz_get_ui(d));


char username[] = "Liam";

FILE *pbfile = fopen("pbfile.txt", "w");

//FILE *pbfile2 = fopen("pbfile2.txt", "w");

//FILE *pvfile = fopen("pvfile.txt", "w");

rsa_write_pub(n, e, s, username, pbfile);

fclose(pbfile);

pbfile = fopen("pbfile.txt", "r");
FILE *pbfile2 = fopen("pbfile2.txt", "w");

rsa_read_pub(nt, e2, s2, username2, pbfile);

rsa_write_pub(nt, e2, s2, username2, pbfile2);

fclose(pbfile2);
fclose(pbfile);

//rsa_write_priv(n, d, pvfile);

//fclose(pvfile);

randstate_clear();
}

