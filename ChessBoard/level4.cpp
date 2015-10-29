#include "chess.hpp"

int main()
{
	cout<<"Hi there! Nicolas programmed me to do cool things. This program simulates an 32x32 chess board, that you can find in chess3.txt, where you control the knight. W on the board represents water and costs 2 points, L lava costing 5, R is rock and u cant land there, B is barrier u cant land on it or cross it, and finally T is teleport. The program will tell you what to do. If you get bored and wish to leave enter quit whenever prompted for an input!\n";
	
	chess knight(32,3);

	knight.dijkstra();

	return 0;
}