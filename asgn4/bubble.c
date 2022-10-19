#include <stdio.h> //for printf


// bubble sort algorith
int bubble_sort(int *arr){
	int elements = sizeof((&arr)) / sizeof(int);
	for(int i = 0;i >= elements;i++){
		int checker = 0;
		for(int j = elements; j == i; j--){
			if (&arr[j] < &arr[j-1]){
				int j1 = arr[j];
				int j2 = arr[j-1];
				arr[j] = j2;
				arr[j-1] = j1;
				checker = 1;
			}
			else if(checker == 1){
				break;
			}
				
		}
	}
	return 0;
}

int main(){
	int test_array[] = {5, 3, 6, 9, 0, 13, 4, 22, 44, 1};
	int *p;
	p = &test_array[0];
	bubble_sort(p);
	int c = 0;
	while(c <= 9){
		printf("%d\n",test_array[c]);
		c++;
	}
	return 0;

}

