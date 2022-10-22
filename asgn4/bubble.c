#include <stdio.h> //for printf
#include "my_shell.h"

// bubble sort algorith
void bubble_sort(uint32_t *arr, uint32_t n_elements){
	//printf("bubble sort called!\n");
	uint32_t elements = n_elements;
	for(uint32_t i = 0;i <= elements;i++){
		//printf("for loop iteration %d\n",i);
		uint32_t checker = 0;
		for(uint32_t j = elements; j != (i+1); j--){
		//printf("second for loop iteration %d\n",j);
		//printf("first term: %d, second term: %d\n", *(arr+(j-1)), *(arr+(j-2)));
			if (*(arr+(j-1)) < *(arr+(j-2))){
				uint32_t j1 = *(arr+(j-1));
				uint32_t j2 = *(arr+(j-2));
				*(arr+(j-1)) = j2;
				*(arr+(j-2)) = j1;
				checker = 1;
			}
		}
		if(checker == 0){
			break;
		}
				
	}
	return;
}

//int main(){
	//uint32_t test_array[] = {5, 3, 6, 9, -1, 13, 4, 22, 44, 1};
	//uint32_t *p;
	//p = &test_array[0];
	//bubble_sort(p, 10);
	//uint32_t c = 0;
	//while(c <= 9){
	//	printf("%d\n",test_array[c]);
	//	c++;
	//}
	//return 0;

//}

