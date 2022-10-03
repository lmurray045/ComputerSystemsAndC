#!/bin/bash

#make the collatz file
make

#create a function to print out the x (starting value) and y (length of sequence) coordinate pair of the collatz sequence of a given input
#function name
lengthcoords() {
	#Run collatz into a new output
	./collatz -n $1 > testdata.dat

	#collect the starting value and the length of the total 
	#sequence and store data into respective variables
	#SOURCE CITATION: used instructor provided resource "full 
	#bash guide" (folk.ntnu.no/geirha/bashguide.pdf) for 
	#assistance with the syntax of this line. Found: page 21, 
	#section 3.1
	ycoord=$(head testdata.dat -n 300 | wc -l)
	xcoord=$(echo $1)
	#write data into standard output
	echo $xcoord $ycoord
}
# create a loop to write a series of x y pairs into lengthplot
#print debug
echo "printing length plot data..."
for i in {2..1000}; do
	#print data points
		#debug
	#write data into lengthplot.dat
	#SOURCE CITATION: "append" operand found on pg. 71 of "full 
	#bash guide"
	lengthcoords $i | cat >> lengthplot.dat;
	done
#print debug
echo "done printing"

#create a function to print out the x (starting value) and y (maximum value) coordinate pair of the collatz sequence of a given input
#function name
maxcoords() {
	#Run collatz into a new output
	./collatz -n $1 > maxdata.dat

	#sort maxdata.dat numerically
	#collect the max number
	mycoord=$(sort maxdata.dat -n -r | head -n 1)
	#collect starting value
	mxcoord=$(echo $1)
	#write data into standard output
	echo $mxcoord $mycoord
}
#create a loop to write a series of x y pairs into maxplot
#print debug
echo "printing max plot data..."
for i in {2..1000}; do
	#print data points
	#write data into maxplot.dat
	echo $(maxcoords $i) | cat >> maxplot.dat;
	done
#print debug
echo "done printing max plot data"

#create a function to list the 
histcoords() {
	#Run collatz into a new output
	./collatz -n $1 > testdata.dat

	#collect the starting value and the length of the total 
	#sequence and store data into respective variables
	#SOURCE CITATION: used instructor provided resource "full 
	#bash guide" (folk.ntnu.no/geirha/bashguide.pdf) for 
	#assistance with the syntax of this line. Found: page 21, 
	#section 3.1
	ycoord=$(head testdata.dat -n 300 | wc -l)
	xcoord=$(echo $1)
	#write data into standard output
	echo $xcoord $ycoord
}

#GNU Plot here-doc
#help with line style and point types (in the "set style" command came from "https://www.youtube.com/watch?v=F_XcgIxdExE&t=76s" timestamp: 2:20
gnuplot <<END
	set terminal pdf
	set output "length.pdf"
	set title "Sequence Length Plot"
	set xlabel "N"
	set ylabel "Length"
	set zeroaxis
	plot "lengthplot.dat"
	
	set terminal pdf
	set output "max.pdf"
	set title "Sequence Maximum Value Plot"
	set xlabel "N"
	set ylabel "Maximum Value"
	set zeroaxis
	plot "maxplot.dat"
END

