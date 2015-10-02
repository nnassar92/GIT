#include "pid.hpp"

using namespace std;

pid::pid()
{
	findns();
	findTs();
	changekp();
	changeki();
	changekd();
	er_i=0;
	
	try{x=new float[ns];}
	catch(bad_alloc&){cout<<"allocation failed\n";}	
	
	try{u=new float[4];}
	catch(bad_alloc&){cout<<"allocation failed\n";}	
	
	changefreq();
	
	u[3]=0;
	
	reference();
	initialpos();
}

void pid::changekp()
{
	cout<<"Please enter the proportional gain value:\n";
	kp=parser::inputfloat();
	cout<<"kp="<<kp<<endl;
}

void pid::changeki()
{
	cout<<"Please enter the integral gain value:\n";
	ki=parser::inputfloat();
	cout<<"ki="<<ki<<endl;
}

void pid::changekd()
{
	cout<<"Please enter the derivative gain value:\n";
	kd=parser::inputfloat();
	cout<<"kd="<<kd<<endl;
}

float * pid::control()
{
	u[3]=filter(u[3],kd*(ref-y-er)/Ts);
	//u[3]=kd*(ref-y-er)/Ts;
	er=ref-y;
	er_i+=er;
	u[1]=kp*(er);
	u[2]=ki*Ts*er_i;
	u[0]=u[1]+u[2]+u[3];
	
	return 	u;
}

void pid::initialpos()
{
	cout<<"Enter the initial position coordinates one entry at a time:\n";
	int i;
	for(i=0;i<ns;i++)
	{
		x[i]=parser::inputfloat();
	}
}

void pid::reference()
{
	cout<<"Enter the reference of the system:\n";
	ref=parser::inputfloat();
}

void pid::updatey(float i)
{
	y=i;
}

void pid::updatex(float * a)
{
	int i;
	for(i=0;i<ns;i++)
	{
		x[i]=a[i];
	}
}

void pid::findTs()
{
	int i;
	ifstream myfile ("./code/model.hpp");
	string mystr="";
	while (true)
		{
			if(myfile.is_open())
			{
				string str;
				getline(myfile,str);
				i=str.find("float Ts=");
				if(i>=0)
				{
					int j;
					for(j=9;str[j]!=';';j++){mystr+=str[j];}
					break;
				}
			}
		}
	
	stringstream s;
	s<<mystr;
	s>>Ts;
}

void pid::findns()
{
	int i;
	bool b=false;
	ifstream myfile ("./code/model.hpp");
	string mystr="";
	while (true)
		{
			if(myfile.is_open())
			{
				string str;
				getline(myfile,str);
				i=str.find("ns=");
				if(i>=0)
					{
						int j;
						for(j=1;str[j]!=';';j++)
							{
								if(b){mystr+=str[j];}
								if(str[j]=='='){b=true;}
							}
						break;
					}
				
			}
		}
	
	stringstream s;
	s<<mystr;
	s>>ns;
}

void pid::copyx(float * a)
{
	int i;
	for(i=0;i<ns;i++)
	{
		a[i]=x[i];
	}
}

void pid::updateer(float a)
{
	er=ref-a;
}

void pid::changefreq()
{
	float f;
	cout<<"Please enter the frequency of the low pass filter on the D control (Enter 0 if you don't want a filter):\n";
	while(true)
	{
		f=parser::inputfloat();
		if (f>=0){freq=f;break;}
		cout<<"Enter a positive number";
	}
}

float pid::filter(float a,float b)
{
	if(freq>0)
		{	float tau=2*3.14159/freq;
			return tau/(tau+Ts)*a+Ts/(tau+Ts)*b;}
	else{return b;}
}