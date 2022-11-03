#include "randstate.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h> //for print f
#include <stdbool.h> //for booleans
#include <stdint.h> //for int types 
#include <gmp.h> //for gmp library
#include "stdlib.h"
#include <math.h>

//rsa make pub
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters)
{
	//make p with random bits
	uint64_t bottom_range = nbits / 4;
	uint64_t top_range = ((2 * nbits) / 4) + 1;
	mpz_t brange; mpz_init(brange); mpz_set_ui(brange, bottom_range);
	mpz_t trange; mpz_init(trange); mpz_set_ui(trange, top_range);
	mpz_urandomm(p, state, trange);
	mpz_add(p, p, brange);
	//calculate q bits
	mpz_t one; mpz_init(one); mpz_set_ui(one, 1);
	mpz_t qbt; mpz_init(qbt);
	//calculate bits used by p
	mpz_t psize; mpz_init(psize); mpz_set_ui(psize, mpz_sizeinbase(p, 2));
	// set qbt to 2^bits
	mpz_mul_2exp(qbt, one, nbits);
	// set qbt to 2^bits / psize, to satisfy the logBase(2) (n) = nbits
	mpz_fdiv_q(qbt, qbt, psize);
	//calculate q
	qnbits = mpz_get_ui(qbt)
	bottom_range = qnbits / 4;
	top_range = ((2 * qnbits) / 4) + 1;
	mpz_set_ui(brange, bottom_range);
	mpz_set_ui(trange, top_range);
	mpz_urandomm(q, state, trange);
	mpz_add(q, q, brange);
	
}

