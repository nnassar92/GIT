This is a PID simulator program. All the transformations from continuous to discrete systems were done by the Euler approximation because it is simple and fast. The results were compared to the ones of Simulink and they were matching so I felt no need in adopting a more accurate approach. The first time you compile the program you will be asked to input the model of the system along with the output. The program will create the appropriate .hpp files for them. This is an easier and more efficient approach than parsing the entries of the user. The second time you run the 'make' function, you go in the actual simulator and you can follow instructions to understand what is happening.

When you first want to run the program just enter 'make' in the command line after having changed the directory to this folder. Afterwards hit enter './run1' and follow the instructions on the screen!

If for any reason something goes wrong, copy the code below to the makefile and enter make in the command line.

Please contact me on nnassar92@gmail.com for any questions about the program!

objects=./code/inputmodel.hpp ./code/program1.cpp ./code/parser.cpp

run1: $(objects)
	g++ $(objects) -o run1 -w

.PHONY: clean

clean:
	rm run1 run2
