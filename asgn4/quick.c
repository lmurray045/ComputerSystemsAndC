#include <stdio.h> //for printf
#include <stdlib.h> //atoi
#include "my_shell.h" //for shell_sort
//quick_sort algorithm
int iteration = 1;

void quick_sort(uint32_t *arr, uint32_t n_elements)
{
	printf("arr start: %d, elements: %d\n", *arr, n_elements);
	if(n_elements == 0)
		{
		return;
		}
	uint32_t length = n_elements-1;
	uint32_t SMALL = 4;
	if((length+1) <= SMALL)
		{
		printf("shell sorted\n");
		shell_sort(arr,n_elements);
		return;
		}
	uint32_t h = 0;
	printf("working array: ");
	while(h <= length)
		{
		printf("%d ", *(arr+h));
		h++;
		}
	printf("\n");
	uint32_t pivot = *(arr+(n_elements / 2));
	printf("pivot %u\n", pivot);
	//printf("range: %ld - %u\n",arr, length);
	int counter = length;
	uint32_t pivot_addr = (n_elements / 2);
	while(counter!=0)
		{
		counter--;
		uint32_t l_swap = pivot_addr;
		int l_change = 0;
		uint32_t r_swap = pivot_addr;
		int r_change = 0;
		uint32_t swapped = 0;
		printf("arr + pivot_addr: %d\n",*(arr+(pivot_addr)));
		for(uint32_t l = 0; l != (pivot_addr); l++)
			{
			printf("left value: %d\n", *(arr+l));
			if(*(arr+l)>=pivot)
				{
				l_swap = l;
				l_change = 1;
				break;
				}
			}
		for(uint32_t r = (length); r != (pivot_addr -1); r--)
			{
			printf("right value: %d\n", *(arr+r));
			if(*(arr+r)<pivot)
				{
				r_swap = r;
				r_change = 1;
				break;
				}
			}
		if(l_swap != r_swap)
			{
			uint32_t temp = *(arr+l_swap);
			*(arr+l_swap) = *(arr+r_swap);
			*(arr+r_swap) = temp;
			swapped = 1;
			printf("swapped %d and %d\n",*(arr+l_swap),*(arr+r_swap));
			if(l_change == 0 && r_change == 1)
				{
				pivot_addr = (r_swap);
				}
			if(r_change == 0 && l_change == 1)
				{
				pivot_addr = (l_swap);
				}
			}
		if(swapped == 0)
			{
			break;
			}
		}
	uint32_t c = 0;
	printf("changed array: ");
	while(c <= length)
		{
		printf("%d ", *(arr+c));
		c++;
		}
	printf("\n");
	printf("iteration: %d\n", iteration);
	iteration++;
	printf("left: %d\n",iteration);
	quick_sort(arr, (pivot_addr));
	printf("right: %d\n",iteration);
	quick_sort((arr+pivot_addr), ((n_elements-pivot_addr)));
	

	return;
}

int main()
{
	uint32_t test_array[] = {5, 8, 6, 9, 2, 13, 4, 45, 44, 3};
	uint32_t test_array2[] = {3,2};
	uint32_t *p;
	uint32_t *pd;
	p = &test_array[0];
	pd = &test_array2[0];
	quick_sort(p, 10);
	shell_sort(pd, 2);
	int c = 0;
	printf("shell: %d\n",test_array2[0]);
	printf("shell: %d\n",test_array2[1]);
	while(c <= 9){
		printf("quick: %d\n",test_array[c]);
		c++;
	}
	return 0;
}
