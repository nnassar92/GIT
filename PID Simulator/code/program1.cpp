//This is run first to input the model of the system

#include "inputmodel.hpp"
#include "parser.hpp"

int main()
{
	cout<<"This code was developed by Nicolas Nassar. It is a PID simulator. All transformations form continuous to discrete time were performed using the Euler approximation. While running the program, you can quit whenever by entering 'quit' when prompted for an input. Please enjoy!\n";
	inputmodel();
	
	parser::SecondMake();

	cout<<"Please enter 'make' then './run2' in the command line.\n";

	return 0;
}

