#include <stdio.h> //for printf
#include "bubble.h"//for bubble
#include "heap.h"  //for heap
#include "quick.h" //for quick
#include "shell.h" //for shell
#include <stdlib.h>//for calloc/malloc
#include "stats.h" //for stats
#include "set.h"  //for sets
#include <inttypes.h> //for uint32_t 
#include "mtrand.h"//for mersenne twister
#include <unistd.h> //for optarg functions
#define OPTIONS "absqhr:n:p:H" //defining possible command line inputs


int main(int argc, char **argv)
{	
	// initialize all starting values, setting numerical values to 					 
	//defaults
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
	//start a for loop, iterating for as many command line arguments 
	//inputted
	for(int c = 0; c < (argc-1); c++)
		{
		//collect arguments
		int opt = getopt(argc, argv, OPTIONS);
		//parse the argument, seeing what was inputted
		// if any sorts are enabled, turn that option on
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
		//if help message requested, enable that option
		if(opt=='H')
			{
			H_set = H_set | 1;
			}
		//if numeric option is specified, set the appropriate set
		//to the specified value
		if(opt=='r')
			{
			r_set = set_empty();
			r_set = r_set | strtoul(optarg,NULL,10);
			//increment an additional iteration to account for 
			//the number that followed the argument
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
		//if "all" is specified, enable all
		if(opt == 'a')
			{
			a_set = a_set | 1;
			}
		}
		//if Help is requested, print message and return
		if(H_set == 1)
			{
			printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\nOPTIONS\n   -H              Display program help and usage.\n   -a              Enable all sorts.\n   -b              Enable Bubble Sort.\n   -h              Enable Heap Sort.\n   -q              Enable Quick Sort.\n   -s              Enable Shell Sort.\n   -n length       Specify number of array elements (default: 100).\n   -p elements     Specify number of elements to print (default: 100).\n   -r seed         Specify random seed (default: 13371453).\n");
			H_set = set_empty();
			return 0;
			}
		// if a is specified, enable all sorts
		if(a_set == 1)
			{
			b_set = b_set | 1;
			q_set = q_set | 1;
			s_set = s_set | 1;
			h_set = h_set | 1;
			a_set = set_empty();
			}
		//set the seed to seed input
		mtrand_seed(r_set);
		//allocate space for the random array, and a copy of it
		uint32_t* arr = (uint32_t*)calloc(n_set, sizeof(uint32_t));
		uint32_t* copy = (uint32_t*)calloc(n_set, sizeof(uint32_t));
		//put random number from mersenne twister into each array
		//slot
		for(uint32_t counter=0; counter < n_set; counter++)
			{
			*(arr+counter) = (mtrand_rand64() & 1073741823);
			}
		//run loop as many times as sorts enabled
		int run_var = q_set + b_set + s_set + h_set;
		for(;run_var>0;run_var--) 
			{
			//copy random array onto copy, so that sorting 
			//doesnt effect later arrays 
			for(uint32_t counter2=0; counter2 < n_set; counter2++)
				{
				*(copy+counter2) = *(arr+counter2);
				}
			//reset stats
			Stats start = { 0, 0 };
			//pointer to stats
			Stats *sts = &start;
			//if b is enabled, print sort message
			if(b_set > 0)
				{
				//sort array
				bubble_sort(sts, copy, n_set);
				//print stats
				printf("Bubble Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				//create a loop, printing elements
				uint32_t c = 1;
				while(c <= p_set)
					{
					//if c hits the array limit, stop
					if(c == n_set+1)
						{
						break;
						}
					//print each number
					printf("%13" PRIu32, *(copy+c-1));
					//print newline every 5 numbers
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				//disable b_set
				b_set = set_empty();
				}
			//if h in enabled, print it
			else if(h_set == 1)
				{
				//sort array
				heap_sort(sts, copy, n_set);
				//print stats
				printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				uint32_t c = 1;
				//print each value
				while(c <= p_set)
					{
					//set limit to array element value
					if(c == n_set+1)
						{
						break;
						}
					//print each number, with newlines
					printf("%13" PRIu32, *(copy+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				//disable h value
				h_set = set_empty();
				}
			//if q is enabled, print it
			else if(q_set == 1)
				{
				//sort array
				quick_sort(sts, copy, n_set);
				//print stats
				printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				uint32_t c = 1;
				//print each number
				while(c <= p_set)
					{
					//set limit to array elements
					if(c == n_set+1)
						{
						break;
						}
					//print numbers with newlines
					printf("%13" PRIu32, *(copy+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				//disable q sort
				q_set = set_empty();
				}
			// if s is enabled, print it
			else if(s_set == 1)
				{
				//use heap sort
				shell_sort(sts, copy, n_set);
				//print statistics
				printf("Shell Sort, %u elements, %lu moves, %lu compares\n", n_set, start.moves, start.compares);
				//print each number
				uint32_t c = 1;
				while(c <= p_set)
					{
					//set limit to array elements
					if(c == n_set+1)
						{
						break;
						}
					//print numbers and newlines
					printf("%13" PRIu32, *(copy+c-1));
					if(c%5 == 0)
						{
						printf("\n");
						}
					c++;
					}
				printf("\n");
				//disable s_sort
				s_set = set_empty();
				}
				}
		//free memory
		free(arr);
		free(copy);
		//return
		return 0;
}			

