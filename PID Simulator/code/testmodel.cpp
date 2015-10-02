//#include "model.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

/*void testmodel()
{
	float**xd;
	float u=1;
	float x[]={1.2,1.1};

	xd=model(x,u);
	float*xn;xn=xd[0];
	float*y;y=xd[1];
	cout<<xn[0]<<','<<xn[1]<<','<<*y<<'\n';
};
*/
int main()
{
	float Ts;
	int i;
	ifstream myfile ("model.hpp");
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
	
	cout<<mystr<<endl;
	
	stringstream s;
	s<<mystr;
	s>>Ts;
	//testmodel();
	return 0;	
}
