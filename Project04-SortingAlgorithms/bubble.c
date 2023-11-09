#include <stdio.h> //for printf
#include "bubble.h"
#include "stats.h"

// bubble sort algorith
//define function, accepting stats, an array pointer, and the number of elements
void bubble_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	//create an editable element variable
	uint32_t elements = n_elements;
	// create a for loop, iterating through all the elements
	for(uint32_t i = 0;i <= elements;i++){
		//create a variable to see if any elements have been swapped
		uint32_t checker = 0;
		//loop again, decrementing through remaining elements
		for(uint32_t j = elements; j != (i+1); j--){
			//compare adjacent elements
			if (cmp(stats,*(arr+(j-1)),*(arr+(j-2))) == -1){
				// if left elements is greater, swap them
				swap(stats,(arr+(j-1)),(arr+(j-2)));
				//update checker, stating the swap
				checker = 1;
			}
		}
		//if no swaps occured, break
		if(checker == 0){
			break;
		}
				
	}
	return;
}


