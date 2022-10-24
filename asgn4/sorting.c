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
	getopt(argc, argv, OPTIONS);
	//int a_arg = 0;
	int b_arg = 1;
	int s_arg = 0;
	int q_arg = 0;
	int h_arg = 0;
	uint64_t r_arg = 13371453;
	uint32_t n_arg = 20;
	uint32_t p_arg = 20;
	//int H_arg = 0;
	uint32_t r_num = 0;
	uint32_t n_num = 0;
	uint32_t p_num = 0;
	uint32_t set = set_empty();
	for(int c = 0; c < (argc-1); c++)
		{
		set_insert(set, **(argv+c));
		if(**(argv+c)=='r')
			{
			r_num = strtoul(optarg, NULL, 10);
			}
		if(**(argv+c)=='n')
			{
			n_num = strtoul(optarg, NULL, 10);
			}
		if(**(argv+c)=='p')
			{
			p_num = strtoul(optarg, NULL, 10);
			}
		}
	for(int counter = 1; counter!= argc; counter++)
		{
		if(set_member('b',set) == true)
			{
			b_arg = 1;
			set_remove('b', set);
			}
		if(set_member('s',set) == true)
			{
			s_arg = 1;
			set_remove('s', set);
			}
		if(set_member('q',set) == true)
			{
			q_arg = 1;
			set_remove('q', set);
			}
		if(set_member('h',set) == true)
			{
			h_arg = 1;
			set_remove('h', set);
			}
		if(set_member('r',set) == true)
			{
			r_arg = r_num;
			set_remove('r', set);
			}
		if(set_member('n',set) == true)
			{
			n_arg = n_num;
			set_remove('n', set);
			}
		if(set_member('p',set) == true)
			{
			p_arg = p_num;
			set_remove('p', set);
			}
		//if(set_member('H',set) == true)
			//{
			//H_arg = 1;
			//set_remove('H', set);
			//}
		//if(set_member('a',set) == true)
			//{
			//a_arg = 1;
			//set_remove('a', set);
			//}
		}
		mtrand_seed(r_arg);
		uint32_t* arr = (uint32_t*)calloc(n_arg, sizeof(uint32_t));
		int run_var = q_arg + b_arg + s_arg + h_arg;
		for(uint32_t counter=0; counter < n_arg; counter++)
			{
			*(arr+counter) = (mtrand_rand64() & 2147483647);
			}
		
		for(;run_var>0;run_var--) 
			{
			Stats start = { 0, 0 };
			Stats *sts = &start;
			if(q_arg == 1)
				{
				quick_sort(sts, arr, n_arg);
				printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_arg, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_arg)
					{
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				q_arg = 0;
				}
			else if(b_arg == 1)
				{
				bubble_sort(sts, arr, n_arg);
				printf("Bubble Sort, %u elements, %lu moves, %lu compares\n", n_arg, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_arg)
					{
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				b_arg = 0;
				}
			else if(s_arg == 1)
				{
				shell_sort(sts, arr, n_arg);
				printf("Shell Sort, %u elements, %lu moves, %lu compares\n", n_arg, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_arg)
					{
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				s_arg = 0;
				}
			else if(h_arg == 1)
				{
				heap_sort(sts, arr, n_arg);
				printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_arg, start.moves, start.compares);
				uint32_t c = 1;
				while(c <= p_arg)
					{
					printf("%13" PRIu32, *(arr+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				h_arg = 0;
				}
				}
}			

