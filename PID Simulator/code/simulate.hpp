//This Function performs the simulation for the time desired and logs the data


#include "pid.hpp"
#include "model.hpp"
#include "output.hpp"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

using namespace std;

void simulate(pid& PID,float t)
{
	float *x;
	
	try{x=new float[PID.getns()];}
	catch(bad_alloc&){cout<<"failed to allocate";};
	
	float Ts=PID.getTs();
	
	float y;float *u;
	
	PID.copyx(x);
	y=output(x);
	PID.updateer(y);
	
	ofstream file;
	file.open("values.csv",ios::out|ios::trunc);
	file<<"t,"<<"y,"<<"u,"<<"er"<<endl;
	
	srand(time(NULL));
	
	cout<<"Please enter the value of random error percentage you want in your system:\n";
	float rerror;
	while (true)
	{
		rerror=parser::inputfloat();
		if (rerror>=0){break;}
		cout<<"Please insert a positive number!\n";
	}
	cout<<"Processing...\n";
	
	int i;
	for (i=0;i<t/Ts+1;i++)
	{
		float *xn;
		PID.updatey(y);
		u=PID.control();
		xn=model(x,u[0]);
		int j;
		for(j=0;j<PID.getns();j++)
			{
				x[j]=xn[j]+xn[j]*rerror*0.1*(rand()%21-10)/100;
			}
		PID.updatex(x);
		
		file<<i*Ts<<','<<y<<','<<u[0]<<','<<PID.geter()<<endl;
		
		y=output(x);
	}
	
	file.close();
	
	delete[]x;
}