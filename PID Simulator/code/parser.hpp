#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;
namespace parser
{
	int inputint();								//Makes sure the input is an integer that it returns
	void inputmodelct(int a);					//Parse a continuous model
	float inputmodeldt(int a);					//TParse a discrete model
	string editct(string n);					//Transform a ct model to dt. It is made using the Euler approx.
	void savemod(string model,int ns,float Ts);	//Saves the model in a .hpp file
	float inputfloat();							//Makes sure the input is a float that it returns
	void saveout(string output);				//Saves the output in a .hpp file
	float find(float,float,int);				//Finds the value needed in the simulation log file
	void Exit();								//Exits the program safely
	void FirstMake();							//Writes the first make file
	void SecondMake();							//Writes the second make file
	void changefile(float,float,float);			//It changes the log according to the sampling frequency needed
};
