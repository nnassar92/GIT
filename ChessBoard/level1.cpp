#include "chess.hpp"

int main()
{
	cout<<"Hi there! Nicolas programmed me to do cool things. This program simulates an 8x8 chess board where you control the knight. The program will tell you what to do. If you get bored and wish to leave enter quit whenever prompted for an input!\n";
	
	chess knight(8,1);

	knight.level1();

	return 0;
}