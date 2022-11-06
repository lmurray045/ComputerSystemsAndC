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
	//make p with random bits
	uint64_t bottom_range = nbits / 4;
	uint64_t top_range = ((2 * nbits) / 4) + 1;
	mpz_t pbt; mpz_init(pbt);
	mpz_t trange; mpz_init(trange); mpz_set_ui(trange, top_range);
	mpz_t brange; mpz_init(brange); mpz_set_ui(brange, bottom_range);
	mpz_urandomm(pbt, state, trange);
	mpz_add(pbt, pbt, brange);
	
	uint64_t pnbits = mpz_get_ui(pbt);
	//make p prime number
	make_prime(p, pnbits, iters);
	//calculate q bits
	//calculate q
	uint64_t qnbits = nbits - pnbits;
	make_prime(q, qnbits, iters);
	//calculate lambda 
	//declare variables
	mpz_t qm1; mpz_init(qm1);
	mpz_t pm1; mpz_init(pm1);
	mpz_t lam; mpz_init(lam);
	mpz_t prod; mpz_init(prod);
	//find q-1 and p-1
	mpz_sub_ui(qm1, q, 1);
	mpz_sub_ui(pm1, p, 1);
	mpz_mul(prod, qm1, pm1);
	//find lambda
	gcd(lam, qm1, pm1);
	mpz_fdiv_q(lam, prod, lam);
	//find e
	mpz_t test; mpz_init(test);
	uint64_t e_top = (3 * nbits) / 4;
	uint64_t e_bot = nbits / 2;
	mpz_urandomb(e, state, e_top);
	mpz_add_ui(e, e, e_bot);
	gcd(test, e, lam);
	while(mpz_cmp_ui(test, 1) != 0)
		{
		mpz_urandomb(e, state, e_top);
		mpz_add_ui(e, e, e_bot);
		gcd(test, e, lam);
		}
	mpz_mul(n, p, q);
	mpz_clear(pbt); mpz_clear(qm1); mpz_clear(pm1);
	mpz_clear(test); mpz_clear(trange); mpz_clear(brange); 
	mpz_clear(lam); mpz_clear(prod);
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
	return;
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
	mpz_clear(lam); mpz_clear(pm1); mpz_clear(qm1); mpz_clear(gc);
	return;
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile)
{
	gmp_fscanf(pvfile, "%Zx\n", n);
	gmp_fscanf(pvfile, "%Zx\n", d);
	return;
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile)
{
	gmp_fscanf(pbfile, "%Zx\n", n);
	gmp_fscanf(pbfile, "%Zx\n", e);
	gmp_fscanf(pbfile, "%Zx\n", s);
	fscanf(pbfile, "%s\n", username);
	return;
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile)
{
	gmp_fprintf(pvfile, "%Zx\n", n);
	gmp_fprintf(pvfile, "%Zx\n", d);
	return;
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n)
{
	pow_mod(c, m, e, n);
	return;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e)
{
	//SOURCE: this function was found in the GMP misceleanous functions 
	//manual page, 5.15.
	mpz_t m; mpz_init(m);
	mpz_t c; mpz_init(c);
	int k = mpz_sizeinbase(n, 2);
	k = (k - 1) / 8;
	uint8_t * block = calloc(k, sizeof(uint8_t));
	*block = 0xFF;
	for(int ch = getc(infile); (ch != EOF);)
		{
		int j = 1;
		for(; j <= (k-1) && ch != EOF; j++)
			{
			*(block+j) = ch;
			ch = getc(infile);
			}
		mpz_import(m, (j), 1, sizeof(*block), 1, 0, block);
		rsa_encrypt(c, m, e, n);
		gmp_printf("c: %Zx\n", c);
		gmp_fprintf(outfile, "%Zx\n", c);
		} 
	mpz_clear(m); mpz_clear(c);
	return;
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n)
{
	pow_mod(m, c, d, n);
	return;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d)
{
	//SOURCE: this function was found in the GMP misceleanous functions 
	//manual page, 5.15.
	mpz_t m; mpz_init(m);
	mpz_t cm; mpz_init(cm); mpz_set_ui(cm, 0);
	uint64_t jv = 0;
	uint64_t * j = &jv;
	
	int k = mpz_sizeinbase(n, 2);
	k = (k - 1) / 8;
	uint8_t * block = calloc(k, sizeof(uint8_t));
	gmp_fscanf(infile, "%Zx", cm);
	do
		{
		rsa_decrypt(m, cm, d, n);
		mpz_export(block, j, 1, sizeof(uint8_t), 1, 0, m);
		for(uint64_t counter = 1; counter < jv; counter++)
			{
			fprintf(outfile, "%c", *(block+counter));
			} 
		}
	while(gmp_fscanf(infile, "%Zx", cm) == 1); 
	mpz_clear(m); mpz_clear(cm);
	return;
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n)
{
	pow_mod(s, m, d, n);
	return;
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n)
{
	mpz_t t; mpz_init(t);
	pow_mod(t, s, e, n);
	if(mpz_cmp(t, m) == 0)
		{
		mpz_clear(t);
		return true;
		}
	else
		{
		mpz_clear(t);
		return false;
		}
}


int main(void)
{
randstate_init(1234567);

mpz_t p; mpz_init(p);
mpz_t q; mpz_init(q);
mpz_t n; mpz_init(n);
mpz_t e; mpz_init(e);
mpz_t d; mpz_init(d);
//mpz_t s; mpz_init(s); mpz_set_ui(s, 12345);
/*
mpz_t nt; mpz_init(nt);
mpz_t e2; mpz_init(e2);
mpz_t s2; mpz_init(s2); mpz_set_ui(s, 12345);
mpz_t dt; mpz_init(dt);
*/

uint64_t bits = 64;
uint64_t iters = ( random() % 500 );

rsa_make_pub(p, q, n, e, bits, iters);

rsa_make_priv(d, e, p, q);

printf("p: %lu, q: %lu, n: %lu, e: %lu, d: %lu\n", mpz_get_ui(p), mpz_get_ui(q), mpz_get_ui(n), mpz_get_ui(e), mpz_get_ui(d));

FILE * message = fopen("message.txt", "w");
fprintf(message, "h");
fclose(message);

FILE * message2 = fopen("message.txt", "r");
FILE * cypher = fopen("cypher.txt", "w");

rsa_encrypt_file(message2, cypher, n, e);

fclose(cypher);
fclose(message2);

cypher = fopen("cypher.txt", "r");
FILE * decrypted_message = fopen("decrypted_message.txt", "w");

rsa_decrypt_file(cypher, decrypted_message, n, d);

fclose(decrypted_message);
fclose(cypher);

mpz_t s; mpz_init(s);
mpz_t m; mpz_init(m);
mpz_t m2; mpz_init(m2);


mpz_set_ui(m, 12345);
mpz_set_ui(m, 54321);

rsa_sign(s, m, d, n);

if(rsa_verify(m2, s, e, n) == true)
	{
	printf("true\n");
	}
else
	{printf("false\n");}

/*
char username[] = "Liam";
//public keys
FILE *pbfile = fopen("pbfile.txt", "w");

rsa_write_pub(n, e, s, username, pbfile);

fclose(pbfile);

pbfile = fopen("pbfile.txt", "r");
FILE *pbfile2 = fopen("pbfile2.txt", "w");

rsa_read_pub(nt, e2, s2, username2, pbfile);

rsa_write_pub(nt, e2, s2, username2, pbfile2);

fclose(pbfile2);
fclose(pbfile);
//private keys
FILE *pvfile = fopen("pvfile.txt", "w");

rsa_write_priv(n, d, pvfile);

fclose(pvfile);

pvfile = fopen("pvfile.txt", "r");
FILE *pvfile2 = fopen("pvfile2.txt", "w");

rsa_read_priv(nt, dt, pvfile);

rsa_write_priv(nt, dt, pvfile2);

fclose(pvfile2);
fclose(pvfile);
*/

randstate_clear();
}

