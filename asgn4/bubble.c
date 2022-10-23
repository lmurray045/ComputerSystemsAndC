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

int main(){
	Stats start = { 0,0 };
	Stats *sts = &start;
	uint32_t test_array[] = {5, 3, 6, 9, 2, 13, 4, 22, 44, 1};
	uint32_t *p;
	p = &test_array[0];
	bubble_sort(sts, p, 10);
	printf("moves: %lu\ncompares: %lu\n", start.moves, start.compares);
	uint32_t c = 0;
	while(c <= 9){
		printf("%d\n",test_array[c]);
		c++;
	}
	return 0;

}

