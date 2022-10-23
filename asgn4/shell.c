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
	if(n_elements == 2)
		{
		if(*(arr)>*(arr+1))
			{
			uint32_t temp = *(arr);
			*(arr) = *(arr+1);
			*(arr+1) = temp;
			return;
			}
		else
			{
			return;
			}
		}
	uint32_t elements = n_elements;
	uint32_t start = ((elements * 5) / 11);
	//printf("start: %d\n",start);
	for(uint32_t gap = start; gap > 0; gap = gap_calc(gap)){
		printf("gap: %d\n",gap);
		int c = 0;
		printf("Working array; ");
		while(c <= 9)
			{
			printf("%d ",*(arr + c));
			c++;
			}
		printf("\n");
		for(uint32_t i = gap;i != (elements);i++){
			printf("i: %d\n",i);
			uint32_t j = i;
			uint32_t temp = *(arr+i);
			while(j >= gap && temp < *(arr + (j-gap)))
				{
				*(arr+j) = *(arr+(j-gap));
				j -= gap;
				}
			*(arr+j) = temp;
			}
		}
	return;
	}
int main()
{
	uint32_t test_array[] = {8, 6};
	uint32_t *p;
	p = &test_array[0];
	shell_sort(p, 2);
	int c = 0;
	while(c <= 1){
		printf("shell: %d\n",test_array[c]);
		c++;
	}
	return 0;
}
