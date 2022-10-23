#include <stdio.h> //for printf
#include <stdlib.h> //atoi
#include "shell.h" //for shell_sort
//quick_sort algorithm
int iteration = 1;

void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements)
{
	if(n_elements == 0)
		{
		return;
		}
	uint32_t length = n_elements-1;
	uint32_t SMALL = 6;
	if((length+1) <= SMALL)
		{
		shell_sort(stats, arr,n_elements);
		return;
		}
	uint32_t pivot = *(arr+(n_elements / 2));
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
		for(uint32_t l = 0; l != (pivot_addr); l++)
			{
			if(cmp(stats,*(arr+l),pivot)== 1 || 0)
				{
				l_swap = l;
				l_change = 1;
				break;
				}
			}
		for(uint32_t r = (length); r != (pivot_addr -1); r--)
			{
			if(cmp(stats,*(arr+r),pivot)==-1)
				{
				r_swap = r;
				r_change = 1;
				break;
				}
			}
		if(l_swap != r_swap)
			{
			swap(stats,(arr+l_swap),(arr+r_swap));
			swapped = 1;
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
	quick_sort(stats, arr, (pivot_addr));
	quick_sort(stats, (arr+pivot_addr), ((n_elements-pivot_addr)));
	return;
}

int main(){
	Stats start = { 0,0 };
	Stats *sts = &start;
	uint32_t test_array[] = {5, 3, 6, 9, 2, 13, 4, 22, 44, 1};
	uint32_t *p;
	p = &test_array[0];
	quick_sort(sts, p, 10);
	printf("moves: %lu\ncompares: %lu\n", start.moves, start.compares);
	uint32_t c = 0;
	while(c <= 9){
		printf("%d\n",test_array[c]);
		c++;
	}
	return 0;
}
