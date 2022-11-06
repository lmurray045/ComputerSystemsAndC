#include "randstate.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h> //for print f
#include <stdbool.h> //for booleans
#include <stdint.h> //for int types 
#include <gmp.h> //for gmp library
#include <stdarg.h>
#include "stdlib.h"
#include <math.h>

gmp_randstate_t state;

//Random initilization functions module

void randstate_init(uint64_t seed)
{
	mpz_t mseed;
	mpz_init(mseed);
	mpz_set_ui(mseed, seed);
	gmp_randinit_mt(state);
	gmp_randseed(state, mseed);
	srand(seed);
	mpz_clear(mseed);
	return;
}
//clear memory w/state
void randstate_clear(void)
{
	gmp_randclear(state);
	return;
}

