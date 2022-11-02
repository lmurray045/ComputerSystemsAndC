#include "randstate.h"
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

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
	return;
}
//clear memory w/state
void randstate_clear(void)
{
	gmp_randclear(state);
	return;
}

