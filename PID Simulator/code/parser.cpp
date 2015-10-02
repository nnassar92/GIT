#include "parser.hpp"
namespace parser{
int inputint()
{
	string input;
	int n;
	float m;
	while (true) {
   		getline(cin, input);

   		stringstream s(input);
  		if (s>>n)		//checking if the input was a number
			{ s>>m;if (n>=0&&m-n<0.00001){break;};}	//checking if the input was a positive integer
		else if (input=="quit")	//quit the program if the user wants to
			{parser::Exit();};
		
   		cout << "\nPlease input a valid integer:" << endl;
 	}
	return n;
}

float inputfloat()
{
	string input;
	float T;
	while (true) {
   		getline(cin, input);

   		stringstream s(input);
  		if (s>>T)		//checking if the input was a number
			{ break;}	//checking if the input was a positive integer
		else if (input=="quit")	//quit the program if the user wants to
			{parser::Exit();};
		
   		cout << "Please input a valid float:" << endl;
 	}
	return T;	
}

void inputmodelct(int ns)
{
	float Ts=0.01;
	//entering the model of the system
	cout<< "Please input the model of the system in the following form:\n"
	    << "xd[0]=f(x[0],...,x[ns],u);..;xd[i]=...;...;xd[ns-1]=...; where ns is the order of the system, example:\n"
	    << "xd[0]=x[0]+cos(u)*x[1];xd[1]=x[0]+u;\n"	
	    << "Please respect the syntax of C++!\n\n";
	
	string modelct;
	getline(cin,modelct);

	cout<<'\n';	
	
	if (modelct=="quit"){parser::Exit();};

	string model;
	model=parser::editct(modelct);
	
	parser::savemod(model,ns,0.001);

	string outputs;

	cout<<"Please insert the equation of the output, in the form of:\n"
	    <<"y=f(x[0],..,x[ns]); Example:\ny=x[0];\n\n";

	getline(cin,outputs);

	parser::saveout(outputs);	

	
}

float inputmodeldt(int ns)
{
	float Ts;
	cout<<"Please enter the time step:\n";
	while (true) {
   		Ts=parser::inputfloat();
		if(Ts>0){break;}
   		cout << "Please input a strictly positive time step:" << endl;
 	}
	cout<< "Please input the model of the system in the following form:\n"
	    << "xn[0]=f(x[0],...,x[ns],u);..;xn[i]=...;...;xn[ns-1]=...; where xn is the updated state and ns is the order of the system, example:\n"
	    << "xn[0]=x[0]+cos(u)*x[1];xn[1]=x[0]+u;\n"	
	    << "Please respect the syntax of C++!\n\n";

	string modeldt;
	getline(cin,modeldt);

	cout<<'\n';	
	
	if (modeldt=="quit"){parser::Exit();}
	
	parser::savemod(modeldt,ns,Ts);

	string outputs;
	
	cout<<"Please insert the equation of the output in the form of:\n"
	    <<"y=f(x[0],..,x[ns]); Example:\ny=x[0];\n\n";

	getline(cin,outputs);

	parser::saveout(outputs);
	
	return Ts;

}

string editct(string n)
{
	int i;
	
	int q=0;
	
	string m="";
	m+=n[0];
	
	for(i=1;i<n.length();i++)
	{
	    if (n[i]=='d'&&n[i-1]=='x')
	    {
	        m+="n";
	    }
	    else if (n[i]=='=')
	    {
	        m+="=(";
	    }
	    else if (n[i]==';')
	    {
	        stringstream ss;
	        string bla; //string carrying the integer
	        ss<<q;
	        ss>>bla;    //converting integer to string
	        
	        m+=")*Ts+x[";
	        m+=bla;
	        m+="];";
	        q++;
	    }
	    else
	    {m+=n[i];}
	   
	}
	
	return m;
}

void savemod(string models,int ns, float Ts)
{
	fstream modfile;
		modfile.open("./code/model.hpp",ios::out|ios::trunc);
		modfile<<"//ns="<<ns<<";\n#include <iostream>\n#include <math.h>\nfloat* model(float* x,float u)"  // I picked Ts to be 0.01s which is 10 times faster than 10Hz which should provide a good estimation to the continuous system
		       <<"{float xn["<<ns<<"];\nfloat Ts="<<Ts<<";\n"<<models<<"\n\nreturn xn;}";
}


void saveout(string outputs)
{
	fstream modfile;
		modfile.open("./code/output.hpp",ios::out|ios::trunc);
		modfile<<"#include <iostream>\n#include <math.h>\nfloat output(float* x)"  // I picked Ts to be 0.01s which is 10 times faster than 10Hz which should provide a good estimation to the continuous system
		       <<"{float y;\n"<<outputs<<"\nreturn y;}";
}

float find(float t,float Ts,int fb)
{
	ifstream file;
	file.open("values.csv");
	
	stringstream s1,s2;
	float res1,res2;
	
	string str;
	string out1="";
	
	int i=0;
	
	float tts=1.0*(int)(t/Ts);
	
	while(i<tts+2)
	{
		getline(file,str);i++;
	}
	
	int count=0;
	i=0;
	while(i<str.length())
	{
		
		if(str[i]==','){count++;}
		else if(count==fb)
		{
			out1+=str[i];
		}
		else if(count>fb){break;}
		i++;
	}
	string out2="";
	getline(file,str);
	count=0;
	i=0;
	while(i<str.length())
	{
		
		if(str[i]==','){count++;}
		else if(count==fb)
		{
			out2+=str[i];
		}
		else if(count>fb){break;}
		i++;
	}
	
	if(fb==2){str="feedback";}
	else{str="control";}
	
	s1<<out1;
	s1>>res1;
	s2<<out2;
	s2>>res2;
	
	file.close();
	
	return (res1*(tts*Ts+Ts-(t-Ts/10))/Ts+res2*((t-Ts/10)-tts*Ts)/Ts);
}

void Exit()
{
	FirstMake();
	exit(0);
}
void FirstMake()
{
	ofstream make1;
	make1.open("makefile",ios::out|ios::trunc);
	make1<<"objects=./code/inputmodel.hpp ./code/program1.cpp ./code/parser.cpp\n\nrun1: $(objects)\n\tg++ $(objects) -o run1 -w\n\n.PHONY: clean\n\nclean:\n\trm run1 run2";
	make1.close();
}

void SecondMake()
{
	ofstream make1;
	make1.open("makefile",ios::out|ios::trunc);
	make1<<"objects= ./code/Part1.cpp ./code/simulate.hpp ./code/parser.cpp ./code/pid.cpp ./code/model.hpp ./code/output.hpp\n\nrun2: $(objects)\n\tg++ $(objects) -o run2 -w\n\n.PHONY: clean\n\nclean:\n\trm run2 run1";
	make1.close();
} 

void changefile(float fre,float Ts,float t)
{
	
	ofstream file;
	file.open("Values.csv",ios::out|ios::trunc);
	file<<"t,"<<"y,"<<"u,"<<"er"<<endl;
	
	int i=0;
	while(1/fre*i<t)
	{
		file<<1/fre*i<<','<<find(1/fre*i,Ts,1)<<','<<find(1/fre*i,Ts,2)<<','<<find(1/fre*i,Ts,1)<<endl;
		i++;
	}
	file.close();
}

}