
##### Liam Murray

##### lijamurr

##### cse13s - FALL 2022

##### October 24, 2022

#			All Sorts of C Code

### Purpose and Usage

The purpose of the the included programs is test different sorting algorithms
with randomized inputs, and compare them using generated statistics about
the comparisons and swaps performed throughout the sorting proccess.

In order to use the program, navigate to the appropriate directory, and run
either "make", "make sorting", or "make all". After the executable is created,
running ./sorting will run the program with the default settings.
Running "make clean" will remove all the derived files made during compilation.

### Available Commands

   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]
OPTIONS
  -H              Display program help and usage.
  -a              Enable all sorts.
  -b              Enable Bubble Sort.
  -h              Enable Heap Sort.
  -q              Enable Quick Sort. 
  -s              Enable Shell Sort.
  -n length       Specify number of array elements (default: 100).
  -p elements     Specify number of elements to print (default: 100).
  -r seed         Specify random seed (default: 13371453).
  
### Bugs

The only errors detected with this program is that the quicksort algorithm
is not as efficent as the examples given, and reports more comparisons and 
swaps than the professor implemented version.

