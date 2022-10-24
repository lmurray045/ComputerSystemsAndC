#include <stdio.h> //for printf
#include "bubble.h"
#include "stats.h"

// bubble sort algorith
void bubble_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	uint32_t elements = n_elements;
	for(uint32_t i = 0;i <= elements;i++){
		uint32_t checker = 0;
		for(uint32_t j = elements; j != (i+1); j--){
			if (cmp(stats,*(arr+(j-1)),*(arr+(j-2))) == -1){
				swap(stats,(arr+(j-1)),(arr+(j-2)));
				checker = 1;
			}
		}
		if(checker == 0){
			break;
		}
				
	}
	return;
}


