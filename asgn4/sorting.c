#include <stdio.h> //for printf
#include "bubble.h"//for bubble
#include "heap.h"  //for heap
#include "quick.h" //for quick
#include "shell.h" //for shell
#include <stdlib.h>//for calloc/malloc
#include "stats.h" //for stats
#include "set.h"  //for sets
#include <inttypes.h>
#include "mtrand.h"//for mersenne twister
#include <unistd.h> //for optarg
#define OPTIONS "absqhr:n:p:H"


int main(int argc, char **argv)
{	
	Set b_set = set_empty();
	Set s_set = set_empty();
	Set q_set = set_empty();
	Set h_set = set_empty();
	Set r_set = set_empty(); 
	Set a_set = set_empty();
	r_set = r_set | 13371453;
	Set n_set = set_empty();
	n_set = n_set | 100;
	Set p_set = set_empty();
	p_set = p_set | 100;
	Set H_set = set_empty();

	for(int c = 0; c < (argc-1); c++)
		{
		int opt = getopt(argc, argv, OPTIONS);
		if(opt=='b')
			{
			b_set = b_set | 1;
			}
		if(opt=='q')
			{
			q_set = q_set | 1;
			}
		if(opt=='s')
			{
			s_set = s_set | 1;
			}
		if(opt=='h')
			{
			h_set = h_set | 1;
			}
		if(opt=='H')
			{
			H_set = H_set | 1;
			}
		if(opt=='r')
			{
			r_set = set_empty();
			r_set = r_set | strtoul(optarg,NULL,10);
			c++;
			}
		if(opt=='n')
			{
			n_set = set_empty();
			n_set = n_set | strtoul(optarg, NULL, 10);
			c++;
			}
		if(opt=='p')
			{
			p_set = set_empty();
			p_set = p_set | strtoul(optarg, NULL, 10);
			c++;
			}
		if(opt == 'a')
			{
			a_set = a_set | 1;
			}
		}
		if(H_set == 1)
			{
			printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\nOPTIONS\n   -H              Display program help and usage.\n   -a              Enable all sorts.\n   -b              Enable Bubble Sort.\n   -h              Enable Heap Sort.\n   -q              Enable Quick Sort.\n   -s              Enable Shell Sort.\n   -n length       Specify number of array elements (default: 100).\n   -p elements     Specify number of elements to print (default: 100).\n   -r seed         Specify random seed (default: 13371453).\n");
			H_set = set_empty();
			return 0;
			}
		if(a_set == 1)
			{
			b_set = b_set | 1;
			q_set = q_set | 1;
			s_set = s_set | 1;
			h_set = h_set | 1;
			a_set = set_empty();
			}
		mtrand_seed(r_set);
		uint32_t* arr = (uint32_t*)calloc(n_set, sizeof(uint32_t));
		int run_var = q_set + b_set + s_set + h_set;
		for(uint32_t counter=0; counter < n_set; counter++)
			{
			*(arr+counter) = (mtrand_rand64() & 1073741823);
			}
		
		for(;run_var>0;run_var--) 
			{
			Stats start = { 0, 0 };
			Stats *sts = &start;
			if(q_set > 0)
				{
				quick_sort(sts, arr, n_set);
				printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_set)
					{
					if(c == n_set+1)
						{
						break;
						}
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				q_set = set_empty();
				}
			else if(b_set == 1)
				{
				bubble_sort(sts, arr, n_set);
				printf("Bubble Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_set)
					{
					if(c == n_set+1)
						{
						break;
						}
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				b_set = set_empty();
				}
			else if(s_set == 1)
				{
				
				shell_sort(sts, arr, n_set);
				printf("Shell Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_set)
					{
					if(c == n_set+1)
						{
						break;
						}
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				s_set = set_empty();
				}
			else if(h_set == 1)
				{
				heap_sort(sts, arr, n_set);
				printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_set)
					{
					if(c == n_set+1)
						{
						break;
						}
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				h_set = set_empty();
				}
				}
		free(arr);
		return 0;
}			

