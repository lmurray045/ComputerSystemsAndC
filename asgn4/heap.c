#include <stdio.h> //for printf
#include <stdint.h> // for uint32_t
#include <stdlib.h> //for calloc
#include "stats.h"

//left child
//calculate the address of the inputs left child
uint32_t left_child(uint32_t addr)
	{
	return ((2*addr) + 1);
	}

//right child
//calculate the address of the inputs right child
uint32_t right_child(uint32_t addr)
	{
	return ((2*addr) + 2);
	}

//parent
//calculate the address of the inputs parent
uint32_t parent(uint32_t addr)
	{
	return ((addr - 1) / 2);
	}

//up heap
//define the upheap function, used to adjust elements in the heap
void up_heap(Stats *stats, uint32_t *arr, uint32_t element)
	{
	uint32_t n = element;
	//while an element is less than its parent, swap them up the heap
	while( n > 0 && (cmp(stats,*(arr+n),*( arr + parent(n) )) == -1) )
		{
		//swap elements
		swap(stats,(arr+n),(arr + (parent(n))));
		//update the element being viewed
		n = parent(n);
		}
	}

//down heap
//used to "remove" an element from the heap and adjust the rest
void down_heap(Stats *stats, uint32_t *arr, uint32_t elements)
	{
	uint32_t n = 0;
	uint32_t smaller;
	//while loop, while there are still unparsed elements
	while(left_child(n) < elements)
		{
		//if theres no right child, the left is smaller
		if(right_child(n) == elements)
			{
			smaller = left_child(n);
			}
		else
			{
			//compare the children, collecting the smaller one
			if(cmp(stats,*(arr+left_child(n)), *(arr+right_child(n)))==-1)
				{
				smaller = left_child(n);
				}
			else
				{
				smaller = right_child(n);
				}
			}
		//if the parent is smaller than the smallest child, stop
		if(cmp(stats, *(arr+n), *(arr+smaller))==-1)
			{
			break;
			}
		//otherwise, swap them, and set n to smaller
		swap(stats, (arr+n), (arr+smaller));
		n = smaller;
		}
	return;
	}

//build heap
//used to create the heap
void build_heap(Stats *stats, uint32_t *arr, uint32_t n_elements)
	{
	//set the heap array so that the heap condition is maintained
	for(uint32_t n = 0; n < n_elements; n++)
		{
		up_heap(stats, arr, n);
		}
	}

//heap sort
void heap_sort(Stats *stats, uint32_t *arr, uint32_t elements)
{	
	//copy the array, so the main array can function as a sorted list
	uint32_t* copy = (uint32_t*)calloc(elements, sizeof(uint32_t));
	//copy main array to copy
	for(uint32_t c = 0;c < elements;c++)
		{
		*(copy+c) = *(arr+c);
		}
	//build the heap with the copy
	build_heap(stats, copy, elements);
	//for loop, for as many elements there are
	for(uint32_t n = 0; n < elements; n++)
		{
		//set the nth array element to the first element of the heap (copy)
		move(stats, *(arr+n));
		*(arr+n) = *(copy);
		move(stats, *(copy));
		//"remove" the transferred element from the heap
		*(copy) = *(copy+(elements-n-1));
		move(stats, *(copy+(elements-n-1)));
		//adjust heap to reflect removed element
		down_heap(stats, copy, (elements-n));
		}
	//free memory
	free(copy);
	return;
}

