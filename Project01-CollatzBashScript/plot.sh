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
	# remove outliers that skew data
	if (( mycoord > 100000 )); then mycoord=0; fi
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
#create a function to output the starting sequence value and the total value of all of its constituents as an x y coordinate pair
#function name
totalcoords() {
	#run collatz into an output file
	./collatz -n $1 > totaldata.dat
	
	#collect the total value of the sequence
	#counter variable
	declare -i runningtotal
	runningtotal=0
	FILE=$(head totaldata.dat -n 400)
	#make a loop iterating through the lines of the file
	for i in $FILE; do
		#add value to the running total
		runningtotal+=$i;
		done
	#collect data in the y coordinate variable
	ycoord=$runningtotal
	#remove outliers
	if (( ycoord > 500000 )); then ycoord=0; fi
	#collect the starting value
	xcoord=$(echo $1)	
	#write data into the standard output
	echo $xcoord $ycoord
}
#create a loop to write a series of x y pairs into length plot, maxplot, and 
#totalplot
for i in {2..10000}; do
	#write data into maxplot.dat and lengthplot.dat, and totalplot.dat
	maxcoords $i | cat >> maxplot.dat;
	lengthcoords $i | cat >> lengthplot.dat;
	totalcoords $i | cat >> totalplot.dat;
	done

#create a loop to add the lengths of a range of Collatz sequences to a data file for the histogram
for i in {2..10000}; do
	echo $(histolength $i) >> temp.dat;
	done
#SOURCE CITATION: how to use the awk command: https://www.youtube.com/watch?v=fRZvwBevctA  as well as awk manual (unix)
#Filter the data, counting how often each length appears, and switch into appropriate x, y coordinate positions
uniq -c temp.dat | awk -F" " '{ print $2,$1 }' | sort -n >> histoplot.dat


#GNU Plot here-doc (length, max and total value)
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
	
	set terminal pdf
	set output "total_collatz_sequence_value.pdf"
	set title "Total Collatz Sequence Value"
	set xlabel "n"
	set ylabel "total value"
	set zeroaxis
	plot "totalplot.dat"
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
rm testdata.dat && rm lengthplot.dat && rm histodata.dat && rm maxplot.dat && rm maxdata.dat && rm temp.dat && rm histoplot.dat && rm totaldata.dat && rm totalplot.dat

