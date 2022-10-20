#include <stdio.h> //for printf


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

int shell_sort(int *arr, int n_elements){
	int elements = n_elements;
	int start = ((elements * 5) / 11);
	printf("start: %d\n",start);
	for(int gap = start; gap > 0; gap = gap_calc(gap)){
		printf("gap: %d\n",gap);
		for(int i = gap;i != (elements);i++){
			printf("i: %d\n",i);
			for(int j = i;j > (gap-1);j = j - gap){
				printf("j: %d\n",j);
				printf("gap - 1: %d\n",(gap-1));
				printf("Elements: %d, %d\n",*(arr+(j)),*(arr+(j-gap)));
				if (*(arr+(j)) < *(arr+(j-gap))){
					printf("swapped\n");
					int temp = *(arr+(j));
					*(arr+(j)) = *(arr+(j-gap));
					*(arr+(j-gap)) = temp;
				}
			
			}
		}
	}
	return 0;

}

int main(){
	int test_array[] = {5, 3, 6, 9, -1, 13, 4, 22, 44, 1};
	int *p;
	p = &test_array[0];
	shell_sort(p, 10);
	int c = 0;
	while(c <= 9){
		printf("%d\n",test_array[c]);
		c++;
	}
	return 0;
	
}
