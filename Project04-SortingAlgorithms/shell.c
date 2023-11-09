#include <stdio.h> //for printf
#include "stats.h"

//shell sort code
//gap calculation
int gap_calc(int n){
	//if n is one, stop
	if(n==1){
		return 0;
	}
	//if n is 2 or less, the gap is one
	else if(n<=2){
		n=1;
	}
	//otherwise its (N*5) / 11
	else
		n = ((n * 5) / 11);
	return n;
	
		
}
//shell sort algorithm definition
void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	//if only two elements, compare and swap them
	if(n_elements == 2)
		{
		//this shortcuts the process and makes 2 element arrays really fast
		if(cmp(stats,*(arr),*(arr+1)) == 1)
			{
			swap(stats, (arr),(arr+1));
			return;
			}
		else
			{
			return;
			}
		}
	//make editable elements variable
	uint32_t elements = n_elements;
	//calculate the first gap
	uint32_t start = ((elements * 5) / 11);
	//for loop, until gap is 0 (when n = 1)
	for(uint32_t gap = start; gap > 0; gap = gap_calc(gap)){
		//for loop, iterating from the gap to the number of elements
		for(uint32_t i = gap;i != (elements);i++){
			//initilize j to i
			uint32_t j = i;
			uint32_t temp = move(stats, *(arr+i));
			//loop while j is larger than the gap, and while j-gap element is larger than the ith element 
			while(j >= gap && cmp(stats,temp,*(arr + (j-gap)))==-1)
				{
				move(stats, 1);
				//edit arr+j element to be j -gap
				*(arr+j) = move(stats, *(arr+(j-gap)));
				j -= gap;
				}
			move(stats, *(arr+j));
			//update arr+jth element
			*(arr+j) = temp;
			}
		}
	return;
	}
