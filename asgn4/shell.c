#include <stdio.h> //for printf
#include "stats.h"

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

void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	if(n_elements == 2)
		{
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
	uint32_t elements = n_elements;
	uint32_t start = ((elements * 5) / 11);
	for(uint32_t gap = start; gap > 0; gap = gap_calc(gap)){
		for(uint32_t i = gap;i != (elements);i++){
			uint32_t j = i;
			uint32_t temp = move(stats, *(arr+i));
			while(j >= gap && cmp(stats,temp,*(arr + (j-gap)))==-1)
				{
				move(stats, 1);
				*(arr+j) = move(stats, *(arr+(j-gap)));
				j -= gap;
				}
			move(stats, *(arr+j));
			*(arr+j) = temp;
			}
		}
	return;
	}
//int main(){
	//Stats start = { 0,0 };
	//Stats *sts = &start;
	//uint32_t test_array[] = {5, 3, 6, 9, 2, 13, 4, 22, 44, 1};
	//uint32_t *p;
	//p = &test_array[0];
	//shell_sort(sts, p, 10);
	//printf("moves: %lu\ncompares: %lu\n", start.moves, start.compares);
	//uint32_t c = 0;
	//while(c <= 9){
		//printf("%d\n",test_array[c]);
		//c++;
	//}
	//return 0;
//}
