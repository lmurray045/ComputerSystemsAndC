#include <stdio.h> //for print f
#include <stdbool.h> //for booleans
#include <stdint.h> //for int types 
#include <gmp.h> //for gmp library


//GCD Function. Used to compute the greatest common divisor of the
void gcd(mpz_t d, mpz_t a, mpz_t b)
{
	mpz_t ta;
	mpz_init(ta);
	mpz_set(ta, a);
	
	mpz_t tb;
	mpz_init(tb);
	mpz_set(tb, b);
	
	mpz_t t;
	mpz_init(t);
	while(mpz_cmp_ui(tb,0)!=0)
		{
		//printf("comparison: %d\n", mpz_cmp_ui(tb,0));
		//gmp_printf("A, B: %d, %d\n", mpz_get_ui(ta), mpz_get_ui(tb));
		mpz_set(t, tb);
		mpz_fdiv_r(tb, ta, tb);
		mpz_set(ta, t);
		}
	mpz_set(d, ta);
	return;
}


int main(void)
{
mpz_t a;
mpz_init(a);
mpz_set_d(a, 27);

mpz_t b;
mpz_init(b);
mpz_set_d(b, 4);

mpz_t d;
mpz_init(d);

gcd(d,a,b);

gmp_printf("the gcd of %d and %d is: %d\n", mpz_get_ui(a), mpz_get_ui(b), mpz_get_ui(d));


return 0;
}
