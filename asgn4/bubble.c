#include <stdio.h> //for printf


// bubble sort algorith
int bubble_sort(int *arr, int n_elements){
	printf("bubble sort called!\n");
	int elements = n_elements;
	for(int i = 0;i <= elements;i++){
		printf("for loop iteration %d\n",i);
		int checker = 0;
		for(int j = elements; j != (i+1); j--){
		printf("second for loop iteration %d\n",j);
		printf("first term: %d, second term: %d\n", *(arr+(j-1)), *(arr+(j-2)));
			if (*(arr+(j-1)) < *(arr+(j-2))){
				int j1 = *(arr+(j-1));
				int j2 = *(arr+(j-2));
				*(arr+(j-1)) = j2;
				*(arr+(j-2)) = j1;
				checker = 1;
			}
		}
		if(checker == 0){
			break;
		}
				
	}
	return 0;
}

int main(){
	int test_array[] = {5, 3, 6, 9, -1, 13, 4, 22, 44, 1};
	int *p;
	p = &test_array[0];
	bubble_sort(p, 10);
	int c = 0;
	while(c <= 9){
		printf("%d\n",test_array[c]);
		c++;
	}
	return 0;

}

