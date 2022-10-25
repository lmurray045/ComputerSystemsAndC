#include <stdio.h> //for printf
#include <stdint.h> // for uint32_t
#include <stdlib.h> //for calloc
#include "stats.h"

//left child
uint32_t left_child(uint32_t addr)
	{
	return ((2*addr) + 1);
	}

//right child
uint32_t right_child(uint32_t addr)
	{
	return ((2*addr) + 2);
	}

//parent
uint32_t parent(uint32_t addr)
	{
	return ((addr - 1) / 2);
	}

//up heap
void up_heap(Stats *stats, uint32_t *arr, uint32_t element)
	{
	uint32_t n = element;
	while( n > 0 && (cmp(stats,*(arr+n),*( arr + parent(n) )) == -1) )
		{
		swap(stats,(arr+n),(arr + (parent(n))));
		n = parent(n);
		}
	}

//down heap
void down_heap(Stats *stats, uint32_t *arr, uint32_t elements)
	{
	uint32_t n = 0;
	uint32_t smaller;
	while(left_child(n) < elements)
		{
		if(right_child(n) == elements)
			{
			smaller = left_child(n);
			}
		else
			{
			if(cmp(stats,*(arr+left_child(n)), *(arr+right_child(n)))==-1)
				{
				smaller = left_child(n);
				}
			else
				{
				smaller = right_child(n);
				}
			}
		if(cmp(stats, *(arr+n), *(arr+smaller))==-1)
			{
			break;
			}
		swap(stats, (arr+n), (arr+smaller));
		n = smaller;
		}
	return;
	}

//build heap
void build_heap(Stats *stats, uint32_t *arr, uint32_t n_elements)
	{
	for(uint32_t n = 0; n < n_elements; n++)
		{
		up_heap(stats, arr, n);
		}
	}

//heap sort
void heap_sort(Stats *stats, uint32_t *arr, uint32_t elements)
{
	uint32_t* copy = (uint32_t*)calloc(elements, sizeof(uint32_t));
	for(uint32_t c = 0;c < elements;c++)
		{
		*(copy+c) = *(arr+c);
		}
	build_heap(stats, copy, elements);
	for(uint32_t n = 0; n < elements; n++)
		{
		move(stats, *(arr+n));
		*(arr+n) = *(copy);
		move(stats, *(copy));
		*(copy) = *(copy+(elements-n-1));
		move(stats, *(copy+(elements-n-1)));
		down_heap(stats, copy, (elements-n));
		}
	free(copy);
	return;
}

