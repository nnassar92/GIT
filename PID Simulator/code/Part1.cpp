//This is the main program that runs everything

#include "simulate.hpp"
#include "stdio.h"

int main()
{
	pid PID;
	
	float t;
	
	cout<<"Please insert the duration of the simulation in seconds:\n";
	
	while (true)
	{
		t=parser::inputfloat();
		if (t>0){break;}
		else {cout<<"Please input a positive number:\n";}
	}
	
	simulate(PID,t);
	cout<<"Done!\n";
	
	if(t>=5&&1.0/PID.getTs()>10)
	{
		cout<<"What frequency would you like the output to be sampled at? Choose the value of Hz between 10 and "<<1.0/PID.getTs()<<"\n";
	
		float fre;
		
		while(true)
		{
			fre=parser::inputfloat();
			if(fre>=10&&fre<=1000){break;}
		}
		
		if(1.0/PID.getTs()-fre>0.001){cout<<"changing file\n";parser::changefile(fre,PID.getTs(),t);t=3;}
		cout<<"Your outputs are stored in a file called values.csv\n";
	}
	
	while(true)
	{
		cout<<"Please enter 'feedback' or 'control' to see any of these signal values at the time you want:\n";
		string str;
		int fb=1;
		while (true)
		{
			getline(cin,str);
			if (str=="feedback"){break;}
			else if (str=="control"){fb=2;break;}
			else if (str=="quit"){if(t<5){remove("values.csv");}parser::Exit();}
			else {cout<<"Wrong input! Try again.\n";}
		}
		
		cout<<"Please enter the time stamp of the value needed:\n";
		
		float tn;
		while(true)
		{
			tn=parser::inputfloat();
			if(tn<0||tn>t){cout<<"Please input a value within the bounds of the simulation!\n";continue;}
			break;
		}
		
		
		
		float p=parser::find(tn+PID.getTs()/10,PID.getTs(),fb);
		
		cout<<"The "<<str<<" signal at time "<<tn<<" is "<<p<<endl;
	}
	
	
	return 0;
}