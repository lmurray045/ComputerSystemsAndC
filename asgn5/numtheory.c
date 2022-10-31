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
//Pow Mod. Raises base to the power of exponent modulo modulus, stored in base
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus)
{
	mpz_t v;
	mpz_init(v);
	mpz_set_d(v, 1);
	
	mpz_t p;
	mpz_init(p);
	mpz_set(p, base);
	
	mpz_t tex;
	mpz_init(tex);
	mpz_set(tex, exponent);
	
	mpz_t rem;
	mpz_init(rem);
	
	while(mpz_cmp_ui(tex,0)!=0)
		{
		mpz_fdiv_r_ui(rem, tex, 2);
		if(mpz_cmp_ui(rem, 0)!=0)
			{
			mpz_mul(v, v, p);
			mpz_fdiv_r(v, v, modulus);
			}
		mpz_mul(p,p,p);
		mpz_fdiv_r(p, p, modulus);
		mpz_fdiv_q_ui(tex, tex, 2);
		}
		mpz_set(out, v);
}

//uses miller-rabin algorithm to test for primality
bool is_prime(mpz_t n, uint64_t iters)
{
	//var for the f in the miller rabin alg
	mpz_t f;
	mpz_init(f);
	mpz_set_ui(f,4);
	//var for n - 1
	mpz_t tn;
	mpz_init(tn);
	mpz_set(tn,n);
	mpz_sub(tn,tn,1);
	//temporary n variable
	mpz_t cn;
	mpz_init(cn);
	mpz_set(cn,n);
	//miller-rabin r
	mpz_t r;
	mpz_init(r);
	mpz_fdiv_r(r, tn, f);
	//miller-rabin s
	mpz_t s;
	mpz_init(s);
	//s-1
	mpz_t sm1;
	mpz_init(sm1);
	//j variable
	mpz_t j;
	mpz_init(j);
	
	uint64_t count = mpz_get_ui(r);
	//calculate r and f
	while((count % 2) = 0)
		{
		mpz_set(s, f);
		mpz_fdiv_r(r, tn, f);
		mpz_mul_ui(f, f, 2);
		count = mpz_get_ui(r);
		}
	uint64_t i = 1;
	while(mpz_cmp(i, iters) != 0)
	 	{
	 	//TODO: a = Random num from 2 - n-2
	 	mpz_t y;
	 	init y; 
	 	pow_mod(y,a,r,cn);
	 	if((mpz_cmp_ui(y,1) != 1) && (mpz_cmp_ui(y, tn)))
	 		{
	 		mpz_set_ui(j,1);
	 		mpz set(sm1, s);
	 		mpz_sub_ui(sm1, 1);
	 		while((mpz_cmp(j, sm1) == -1 || 0) && (mpz_cmp(y,tn) != 0))
	 			{
	 			mpz_t exp; mpz_init(exp); mpz_set_ui(exp,2)
	 			pow_mod(y,y,exp,n);
	 			if(mpz_cmp(y, 1) == 0)
	 				{
	 				return false;
	 				}
	 			mpz_add_ui(j,j,1)
	 			}
	 		if(mpz_cmp(y,tn) != 0)
	 			{
	 			return false;
	 			}
	 			
	 		}
	 	}
	 return true;
}


int main(void)
{
mpz_t a;
mpz_init(a);
mpz_set_d(a, 4);

mpz_t b;
mpz_init(b);
mpz_set_d(b, 45);

mpz_t c;
mpz_init(c);
mpz_set_d(c, 45);

mpz_t d;
mpz_init(d);

gmp_printf("a: %d b: %d c: %d d: %d\n", mpz_get_ui(a), mpz_get_ui(b), mpz_get_ui(c), mpz_get_ui(d));

pow_mod(d,a,b,c);

gmp_printf("the pow_mod of %d and %d mod %d is: %d\n", mpz_get_ui(a), mpz_get_ui(b), mpz_get_ui(c), mpz_get_ui(d));

gmp_printf("a: %d b: %d c: %d d: %d\n", mpz_get_ui(a), mpz_get_ui(b), mpz_get_ui(c), mpz_get_ui(d));

return 0;
}
