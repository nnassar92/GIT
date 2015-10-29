#include "parser.hpp"
namespace parser{
int inputint(string rorc, int size,bool notfirst)
{
	string input;
	int n;
	float m;
	while (true) {
		cout<<"Please input the "<<rorc<<" number between 0-"<<size-1<<endl;
   		getline(cin, input);

   		stringstream s(input);
  		if (s>>n)		//checking if the input was a number
			{ s>>m;if (n>=0&&n<size&&m-n<0.00001){break;};}	//checking if the input was a positive integer
		else if (input=="quit")	//quit the program if the user wants to
			{exit(0);}
			else if (input=="end"&&(rorc=="row"||rorc=="column")&&notfirst)
			{
				return -1;
			}
		
   		cout << "Please input a valid integer within the bounds:" << endl;
 	}
	return n;
}
}
