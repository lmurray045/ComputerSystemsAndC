#include <stdio.h> //for printf
#include "my_shell.h"

//shell sort code

int gap_calc(int n){
	if(n==1){
		return 0;
	}
	else if(n<=2){
		n=1;
	}
	else
		n = ((n * 5) / 11);
	return n;
	
		
}

void shell_sort(uint32_t *arr, uint32_t n_elements){
	uint32_t elements = n_elements;
	uint32_t start = ((elements * 5) / 11);
	//printf("start: %d\n",start);
	for(uint32_t gap = start; gap > 0; gap = gap_calc(gap)){
		//printf("gap: %d\n",gap);
		for(uint32_t i = gap;i != (elements);i++){
			//printf("i: %d\n",i);
			for(uint32_t j = i;j > (gap-1);j = j - gap){
				//printf("j: %d\n",j);
				//printf("gap - 1: %d\n",(gap-1));
				//printf("Elements: %d, %d\n",*(arr+(j)),*(arr+(j-gap)));
				if (*(arr+(j)) < *(arr+(j-gap))){
					//printf("swapped\n");
					uint32_t temp = *(arr+(j));
					*(arr+(j)) = *(arr+(j-gap));
					*(arr+(j-gap)) = temp;
				}
			
			}
		}
	}
	return;
}
