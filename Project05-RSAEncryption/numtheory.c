// clang-format off
#include <stdio.h> //for print f
#include <gmp.h> //for gmp library
// clang-format on
#include "randstate.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h> //for print f
#include <stdbool.h> //for booleans
#include <stdint.h> //for int types 
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>



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
	mpz_set_ui(f,2);
	//var for n - 1
	mpz_t tn;
	mpz_init(tn);
	mpz_set(tn,n);
	mpz_sub_ui(tn,tn,1);
	//temporary n variable
	mpz_t cn;
	mpz_init(cn);
	mpz_set(cn,n);
	//miller-rabin r
	mpz_t r;
	mpz_init(r);
	mpz_fdiv_q(r, tn, f);
	//miller-rabin s
	mpz_t s;
	mpz_init(s);
	mpz_set_ui(s,1);
	//s-1
	mpz_t sm1;
	mpz_init(sm1);
	//j variable
	mpz_t j;
	mpz_init(j);
	//random variable a
	mpz_t a;
	mpz_init(a);
	//
	mpz_t ty; mpz_init(ty); 
	//
	mpz_t exp; mpz_init(exp); 
	
	uint64_t count = mpz_get_ui(r);
	//calculate r and f
	while((count % 2) == 0)
		{
		mpz_add_ui(s, s, 1);
		mpz_mul_ui(f, f, 2);
		mpz_fdiv_q(r, tn, f);
		count = mpz_get_ui(r);
		if(count == 1)
			{
			break;
			}
		}
	uint64_t i = 1;
	while(i != iters)
	 	{
	 	i++;
	 	mpz_sub_ui(tn,tn,3);
	 	mpz_urandomm(a, state, tn);
	 	mpz_add_ui(tn,tn,3);
	 	mpz_add_ui(a,a,2);
	 	mpz_t y;
		mpz_init(y); 
	 	pow_mod(y,a,r,cn);
	 	if((mpz_cmp_ui(y,1) != 0) && (mpz_cmp(y, tn)) != 0)
	 		{
	 		mpz_set_ui(j,1);
	 		mpz_set(sm1, s);
	 		mpz_sub_ui(sm1, sm1, 1);
	 		while((mpz_cmp(j, sm1) != 1) && (mpz_cmp(y,tn) != 0))
	 			{
	 			mpz_set_ui(exp,2);
	 			mpz_set(ty,y);
	 			pow_mod(y,ty,exp,cn);
	 			if(mpz_cmp_ui(y, 1) == 0)
	 				{
	 				return false;
	 				}
	 			mpz_add_ui(j,j,1);
	 			}
	 		if(mpz_cmp(y,tn) != 0)
	 			{
	 			return false;
	 			}
	 			
	 		}
	 	}
	 return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters)
{
	//make and initlize variables
	mpz_t a; mpz_init(a);
	
	mpz_t rnum; mpz_init(rnum);
	//generate the max possible number stored in (bits-1) 
	//(we later bit mask to ensure that this is in the right bit range)
	uint64_t bit_num = pow(2, (bits-1));
	bit_num--;
	//make a random number in that range, stored in a
	mpz_set_ui(rnum, bit_num);
	mpz_urandomm(a, state, rnum);
	//bit mask the msb of a, so that its in our range
	mpz_t bitmask; mpz_init(bitmask);
	//make exponent (bits -1)
	uint64_t exp = (bits-1);
	//make base one
	mpz_t base; mpz_init(base);
	mpz_set_ui(base, 1);
	//set bit mask to 1 * 2^exp, or the msb of bits being one
	mpz_mul_2exp(bitmask, base, exp);
	//bitmask
	mpz_ior(a, a, bitmask);
	//calculate a potentially prime number
	mpz_mul_ui(a,a,6);
	mpz_sub_ui(a,a,1);
	// test if a - 1 is prime
	if(is_prime(a,iters) == 1)
		{
		mpz_set(p, a);
		return;
		}
	//then test if a + 1 is prime
	mpz_add_ui(a, a, 2);
	if(is_prime(a,iters) == 1)
		{
		mpz_set(p, a);
		return;
		}
	while(is_prime(a,iters) == 0)
		{
		mpz_add_ui(a,a,2);
		}
	mpz_set(p,a);
	return;
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n)
{
	//r and r'
	mpz_t r; mpz_init(r); mpz_set(r,n);
	mpz_t rp; mpz_init(rp); mpz_set(rp,a);
	//t and t'
	mpz_t t; mpz_init(t); mpz_set_ui(t,0);
	mpz_t tp; mpz_init(tp); mpz_set_ui(tp,1);
	//q variables initilization
	mpz_t q; mpz_init(q);
	mpz_t qr; mpz_init(qr);
	mpz_t qt; mpz_init(qt);
	//temp initilization
	mpz_t temp; mpz_init(temp);
	
	while(mpz_cmp_ui(rp, 0) != 0)
		{
		//q = r / r'
		mpz_fdiv_q(q, r, rp);
		//set [r, r'] = [r', r - q * r']
		mpz_set(temp, rp);
		mpz_mul(qr,q,rp);
		mpz_sub(rp,r,qr);
		mpz_set(r, temp);
		//set [t, t'] = [t', t - q * t']
		mpz_set(temp, tp);
		mpz_mul(qt,q,tp);
		mpz_sub(tp,t,qt);
		mpz_set(t, temp);
		}
	if(mpz_cmp_ui(r, 1) > 0)
		{
		mpz_set_ui(i, 0);
		return;
		}
	if(mpz_cmp_ui(t,0) < 0)
		{
		mpz_add(t,t,n);
		}
	mpz_set(i, t);
	return;
}
	
