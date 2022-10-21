#include <stdio.h> //for printf
#include <stdlib.h> //atoi
#include "my_shell.h" //for shell_sort
//quick_sort algorithm
int iteration = 1;

int quick_sort(uint32_t *arr, uint32_t n_elements)
{
	uint32_t SMALL = 2;
	uint32_t length = n_elements-1;
	if(length <= SMALL)
		{
		shell_sort(arr,length);
		return 0;
		}
	uint32_t pivot = *(arr+(n_elements / 2));
	printf("pivot %u\n", pivot);
	//printf("range: %ld - %u\n",arr, length);
	int counter = length;
	uint32_t h = 0;
	printf("working array: ");
	while(h <= length)
		{
		printf("%d ", *(arr+h));
		h++;
		}
	printf("\n");
	uint32_t pivot_addr = (length / 2) + 1;
	while(counter!=0)
		{
		counter--;
		uint32_t l_swap = pivot_addr;
		int l_change = 0;
		uint32_t r_swap = pivot_addr;
		int r_change = 0;
		uint32_t swapped = 0;
		printf("arr + pivot_addr: %d\n",*(arr+(pivot_addr)));
		for(uint32_t l = 0; l != (pivot_addr -1); l++)
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
	printf("left:\n");
	quick_sort(arr, (pivot_addr+1));
	printf("right:\n");
	quick_sort((arr+ pivot_addr), (pivot_addr+1));

	return 0;
}

int main()
{
	uint32_t test_array[] = {5, 3, 6, 9, 0, 13, 4, 22, 44, 1};
	uint32_t *p;
	p = &test_array[0];
	quick_sort(p, 10);
	int c = 0;
	while(c <= 9){
		printf("%d\n",test_array[c]);
		c++;
	}
	return 0;
}
