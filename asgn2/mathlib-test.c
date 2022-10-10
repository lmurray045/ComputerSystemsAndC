#include <stdio.h>
#include <math.h>
#include <unistd.h> //for getopt()
#define OPTIONS "scSCTla"
#include "mathlib.h"


// test harness for mathlib.c functions
int print_function(char f) {
	char input = f;
	if (input == 's') {
		double x = 0;
		double increment = (0.05 * M_PI);
		double start = 0;
		double end = 2 * M_PI;
		double my_func = my_sin(x);
		double lib_func = sin(x);
		double diff = (lib_func - my_func);
		printf("  %c            %s           %s       %s\n", 'x', "sin", "Library", "Difference");
		printf("  %c            %s           %s       %s\n", '-', "------", "-------", "----------");
		while (start != end) {
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_func, lib_func, diff);
			start += increment;
			x = start;
			my_func = my_sin(x);
			lib_func = sin(x);
			diff = (lib_func - my_func);
		}
		}
	else if (input == 'c') {
		double x = 0;
		double increment = (0.05 * M_PI);
		double start = 0;
		double end = 2 * M_PI;
		double my_func = my_cos(x);
		double lib_func = cos(x);
		double diff = (lib_func - my_func);
		printf("  %c            %s           %s       %s\n", 'x', "cos", "Library", "Difference");
		printf("  %c            %s           %s       %s\n", '-', "------", "-------", "----------");
		while (start != end) {
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_func, lib_func, diff);
			start += increment;
			x = start;
			my_func = my_cos(x);
			lib_func = cos(x);
			diff = (lib_func - my_func);
		}
		}
	else if (input == 'S') {
		double x = -1;
		double increment = (0.05);
		double start = -1;
		double end = .999;
		double my_func = my_arcsin(x);
		double lib_func = asin(x);
		double diff = (lib_func - my_func);
		printf("  %c            %s           %s       %s\n", 'x', "arcsin", "Library", "Difference");
		printf("  %c            %s           %s       %s\n", '-', "------", "-------", "----------");
		while (start < end) {
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_func, lib_func, diff);
			start += increment;
			x = start;
			my_func = my_arcsin(x);
			lib_func = asin(x);
			diff = (lib_func - my_func);
		}
		}
	else if (input == 'C') {
		double x = -1;
		double increment = (0.05);
		double start = -1;
		double end = .999;
		double my_func = my_arccos(x);
		double lib_func = acos(x);
		double diff = (lib_func - my_func);
		printf("  %c            %s           %s       %s\n", 'x', "arccos", "Library", "Difference");
		printf("  %c            %s           %s       %s\n", '-', "------", "-------", "----------");
		while (start < end) {
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_func, lib_func, diff);
			start += increment;
			x = start;
			my_func = my_arccos(x);
			lib_func = acos(x);
			diff = (lib_func - my_func);
		}
		}
	else if (input == 'T') {
		double x = 1;
		double increment = (0.05);
		double start = 1;
		double end = 9.999;
		double my_func = my_arctan(x);
		double lib_func = atan(x);
		double diff = (lib_func - my_func);
		printf("  %c            %s           %s       %s\n", 'x', "arctan", "Library", "Difference");
		printf("  %c            %s           %s       %s\n", '-', "------", "-------", "----------");
		while (start < end) {
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_func, lib_func, diff);
			start += increment;
			x = start;
			my_func = my_arctan(x);
			lib_func = atan(x);
			diff = (lib_func - my_func);
		}
		}
	else if (input == 'l') {
		double x = 1;
		double increment = (0.05);
		double start = 1;
		double end = 9.999;
		double my_func = my_log(x);
		double lib_func = log(x);
		double diff = (lib_func - my_func);
		printf("  %c            %s           %s       %s\n", 'x', "log", "Library", "Difference");
		printf("  %c            %s           %s       %s\n", '-', "------", "-------", "----------");
		while (start < end) {
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_func, lib_func, diff);
			start += increment;
			x = start;
			my_func = my_log(x);
			lib_func = log(x);
			diff = (lib_func - my_func);
		}
		}
	else {return 1;}
	return 0;
	
}
//SOURCE CITATION: get opt instructions/example taken from assignment 2 instruction document
 int main(int argc, char **argv)
 {
 	int opt = 0;
while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
	switch (opt) {
	case 's':
 		print_function('s');
 		break;
 	case 'c':
 		print_function('c');
 		break;
	case 'C':
 		print_function('C');
 		break;
	case 'S':
 		print_function('S');
 		break;
	case 'T':
 		print_function('T');
 		break;
	case 'l':
 		print_function('l');
 		break;
	case 'a':
		print_function('s');
		print_function('c');
		print_function('S');
		print_function('C');
		print_function('T');
		print_function('l');
		break;
 	}
 	}
 return 0;
 }
