/*
This file takes in the model of the system and creates a .hpp file that 
carries this model. This is an easy way to implement the model rather 
than parsing the raw input of the user into a function. 
*/
#include "parser.hpp"

using namespace std;

int * inputmodel()
{
	float Ts;
	int ns; // # of states
	int ct=-1; // continuous or not	

	
	cout<<"Please enter the number of states:\n";
	while(true)		
		{ns=parser::inputint();if(ns>0){break;}else{cout<<"Can't be zero!\n";}}
	
	cout<<"Is your system continuous or discrete? 1 for continuous 0 for discrete:\n";
	while(true)	
		{ct=parser::inputint();
		if(ct==1 || ct==0){break;}
		else {cout<<"Enter 1 or 0 only!\n";}}		
	
	if(ct==1){parser::inputmodelct(ns);Ts=0.01;}
	else{Ts=parser::inputmodeldt(ns);}
	
	
	
	int n []={ns,Ts};
	return n;
}
	
