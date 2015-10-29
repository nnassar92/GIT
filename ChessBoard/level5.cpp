#include "chess.hpp"

int main()
{
	cout<<"Hello! This program computes the longest path from a start point to an end point. The program will prompt you to define the size of the chess board because the algorithm is computationally extensive.\n";
	
	int i;
	while(true)
	{
		i=parser::inputint("board size",100,false);
		if(i<4){cout<<"Please input a number bigger than 3\n";continue;}
		break;
	}
	
	chess knight(i,5);

	knight.level5();

	return 0;
}