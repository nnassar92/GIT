#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "parser.hpp"

using namespace std;

class pid
{
	private:
		int ns;						//number of states
		float kp;  					//proportional gain
		float ki;					//integral gain
		float kd;					//differential gain
		float er_i;					//summation of errors
		float er;					//error of the system
		float ref;					//reference that the system should follow
		float y;					//current output of the system
		float *x;					//current states of the system
		float * u;					//input to the system
		float Ts;					//Time step
		float freq;					//Low pass filter frequency
		float filter(float,float);	//Filters the differential input
		
	public:
		void changekp(); 			//allows you to change kp
		void changeki();			//allows you to change ki
		void changekd();			//allows you to change kd
		float* control();			//returns current control
		pid();						//constructor
		void initialpos();			//Initializes the initial position
		void reference();			//Sets the reference of the system
		void copyx(float *);		//Copies the values of x into another vector
		float gety(){return y;};	//Returns y
		void updatey(float i);		//Updates y
		int getns(){return ns;};	//Returns the number of states
		float getTs(){return Ts;};	//Returns the time step
		void findTs();				//Finds the time step of the model in the .hpp file
		void findns();				//Finds the # of states of the model in the .hpp file
		void updatex(float * );		//Updates the vector x
		void updateer(float);		//Updates the error of the system
		float geter(){return er;};	//Returns the error of the system
		void changefreq();			//Changes the frequency of the filter of D
};
