#include <stdio.h> //for printf
#include <stdlib.h> //atoi
#include "shell.h" //for shell_sort
#include "stats.h" //for stats
//quick_sort algorithm
//define quicksort
void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements)
{	
	//if there are no more elements, stop
	if(n_elements == 0)
		{
		return;
		}
	//create an editable length variable
	uint32_t length = n_elements-1;
	//if the array is suffeciently small, use shell sort
	uint32_t SMALL = 6;
	if((length+1) <= SMALL)
		{
		shell_sort(stats, arr,n_elements);
		return;
		}
	//calculate the pivot based on an element in the array
	uint32_t pivot = *(arr+(n_elements / 2));
	//make a counter with val length
	int counter = length;
	//store the address of the pivot, to keep track of where it goes
	uint32_t pivot_addr = (n_elements / 2);
	//while there are still elements unparsed
	while(counter!=0)
		{
		//decrement counter
		counter--;
		//create places to store the addresses of values to be swapped
		uint32_t l_swap = pivot_addr;
		//track whether the each side has been swapped
		int l_change = 0;
		uint32_t r_swap = pivot_addr;
		int r_change = 0;
		uint32_t swapped = 0;
		//iterate through the left side
		for(uint32_t l = 0; l != (pivot_addr); l++)
			{
			//if any value is greater than the pivot, stage it to be swapped
			if(cmp(stats,*(arr+l),pivot)== 1 || 0)
				{
				l_swap = l;
				l_change = 1;
				break;
				}
			}
		//iterate through right side
		for(uint32_t r = (length); r != (pivot_addr -1); r--)
			{
			//if any element is less than the pivot, stage it to be swapped
			if(cmp(stats,*(arr+r),pivot)==-1)
				{
				r_swap = r;
				r_change = 1;
				break;
				}
			}
		//if the swap addresses are different, swap the two elements
		if(l_swap != r_swap)
			{
			//swap elements
			swap(stats,(arr+l_swap),(arr+r_swap));
			swapped = 1;
			//if one side has no swappable element, swap with the pivot
			if(l_change == 0 && r_change == 1)
				{
				//track the pivot
				pivot_addr = (r_swap);
				}
			if(r_change == 0 && l_change == 1)
				{
				//track the pivot
				pivot_addr = (l_swap);
				}
			}
		//if no swaps occur, stop
		if(swapped == 0)
			{
			break;
			}
		}
	//call function on left and right side of arrays
	quick_sort(stats, arr, (pivot_addr));
	quick_sort(stats, (arr+pivot_addr), ((n_elements-pivot_addr)));
	return;
}

