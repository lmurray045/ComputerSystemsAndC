#!/bin/bash

#make the collatz file
make

#create a function to print out the x (starting value) and y (length of sequence) coordinate pair of the collatz sequence of a given input
#function name
lengthcoords() {
	#Run collatz into a new output
	./collatz -n $1 > testdata.dat

	#collect the starting value and the length of the total sequence
	#store data into respective files
	echo $1 > x.dat
	head testdata.dat -n 200 | wc -l > y.dat

	#store data in a variable
	#SOURCE CITATION: used instructor provided resource "full bash
	#guide" (folk.ntnu.no/geirha/bashguide.pdf) for assistance with the
	#syntax of this line. Found: page 21, section 3.1
	ycoord=$(head y.dat -n 1)
	xcoord=$(head x.dat -n 1)

	#write data into plot coordinate file
	echo $xcoord $ycoord 
}
# create a loop to write a series of x y pairs into lengthplot
#FOR NEXT SESSION: fix cat replacing than continueing to add data to file
for i in {2..500}; do
	#print data points
	lengthcoords $i
	#write data into lengthplot.dat
	lengthcoords $i | cat > lengthplot.dat;
	done


