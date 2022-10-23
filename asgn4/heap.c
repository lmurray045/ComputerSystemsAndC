#include <stdio.h> //for printf
#include <stdint.h> // for uint32_t
#include <stdlib.h> //for calloc

//left child
uint32_t left_child(uint32_t addr)
	{
	return ((2*addr) + 1);
	}

//right child
uint32_t right_child(uint32_t addr)
	{
	return ((2*addr) + 2);
	}

//parent
uint32_t parent(uint32_t addr)
	{
	return ((addr - 1) / 2);
	}

//up heap
void up_heap(uint32_t *arr, uint32_t element)
	{
	uint32_t n = element;
	while(n > 0 && *(arr+n) < *(arr + (parent(n))))
		{
		uint32_t temp = *(arr+n);
		*(arr+n) = *(arr + (parent(n)));
		*(arr + (parent(n))) = temp;
		n = parent(n);
		}
	}

//down heap
void down_heap(uint32_t *arr, uint32_t elements)
	{
	uint32_t n = 0;
	uint32_t smaller;
	while(left_child(n) < elements)
		{
		if(right_child(n) == elements)
			{
			smaller = left_child(n);
			}
		else
			{
			if(*(arr+left_child(n)) < *(arr+right_child(n)))
				{
				smaller = left_child(n);
				}
			else
				{
				smaller = right_child(n);
				}
			}
		if(*(arr+n) < *(arr+smaller))
			{
			break;
			}
		uint32_t temp = *(arr+n);
		*(arr+n) = *(arr + smaller);
		*(arr + smaller) = temp;
		n = smaller;
		}
	return;
	}

//build heap
void build_heap(uint32_t *arr, uint32_t n_elements)
	{
	for(uint32_t n = 0; n < n_elements; n++)
		{
		up_heap(arr, n);
		}
	}

//heap sort
void heap_sort(uint32_t *arr, uint32_t elements)
{
	uint32_t* copy = (uint32_t*)calloc(elements, sizeof(uint32_t));
	for(uint32_t c = 0;c < elements;c++)
		{
		*(copy+c) = *(arr+c);
		}
	build_heap(copy, elements);
	for(uint32_t n = 0; n < elements; n++)
		{
		*(arr+n) = *(copy);
		*(copy) = *(copy+(elements-n-1));
		down_heap(copy, (elements-n));
		}
	free(copy);
	return;
}

int main()
{
	uint32_t test_array[] = {5, 8, 6, 100, 2, 3, 4, 55, 44, 3};
	uint32_t *p;
	p = &test_array[0];
	heap_sort(p, 10);
	int c = 0;
	while(c <= 9){
		printf("heap: %d\n",test_array[c]);
		c++;
	}
	return 0;
}
