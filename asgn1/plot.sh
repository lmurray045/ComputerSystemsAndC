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

#create a function to list the length value of any given collatz value.
histolength() {
	#Run collatz into a new output
	./collatz -n $1 > histodata.dat

	#collect length of the total sequence 
	ycoord=$(head histodata.dat -n 300 | wc -l)
	#write data into standard output
	echo $ycoord
}

#create a loop to write a series of x y pairs into maxplot
#print debug
echo "printing max plot and length plot data..."
for i in {2..1000}; do
	#write data into maxplot.dat and lengthplot.dat
	maxcoords $i | cat >> maxplot.dat;
	lengthcoords $i | cat >> lengthplot.dat;
	done
#print debug
echo "Printing max and long complete"

#create a loop to add the lengths of Collatz sequences to a data file
for i in {2..1000}; do
	echo $(histolength $i) >> temp.dat;
	done
#SOURCE CITATION: how to use the awk command: https://www.youtube.com/watch?v=fRZvwBevctA  as well as awk manual (unix)
uniq -c temp.dat | awk -F" " '{ print $2,$1 }' | sort -n >> histoplot.dat
echo "done printing histogram data"


#GNU Plot here-doc (length and max value)
#help with line style and point types (in the "set style" command came from "https://www.youtube.com/watch?v=F_XcgIxdExE&t=76s" timestamp: 2:20
gnuplot <<END
	set terminal pdf
	set output "collatz_sequence_lengths.pdf"
	set title "Collatz Sequence Lengths"
	set xlabel "n"
	set ylabel "length"
	set zeroaxis
	plot "lengthplot.dat"
	
	set terminal pdf
	set output "maximum_collatz_sequence_value.pdf"
	set title "Maximum Collatz Sequence Value"
	set xlabel "n"
	set ylabel "value"
	set zeroaxis
	plot "maxplot.dat"
END
#here-doc for the histogram
#SOURCE CITATION: help found from gnuplot > help histogram manual.
gnuplot <<END
	set terminal pdf
	set style data histogram
	set boxwidth 0.9
	set style fill solid 1.0 border -1
	set output "collatz_sequence_length_histogram.pdf"
	set title "Collatz Sequence Length Histogram"
	set xlabel "length"
	set ylabel "frequency"
	set zeroaxis
	plot "histoplot.dat" with boxes
END

# removing the unneccesary files
rm testdata.dat && rm lengthplot.dat && rm histodata.dat && rm maxplot.dat && rm maxdata.dat && rm temp.dat && rm histoplot.dat

