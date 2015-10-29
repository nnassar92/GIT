#include "parser.hpp"

class chess
{
private:
	int size;		//size of the board
	bool initial;	//in level 1 to check if the user is inputing the initial condition or the sequence
	int count;		//used differently in different functions
	int **moves;	//used in level 2 to log the moves of the user
	bool printing;	//to save whether the user wants the results to be printed in level 1
	int **board;	//2D array to store data in levels 3->5
	int visited;	//array to store the visited nodes in the dijkstra algorithm
	bool moveson;	//to check if the moves array was initialized
	bool boardon;	//to check if the board array was initialized
	
	
public:
	chess(int s,int);		//initializer
	void changerows(int);	//update the row 
	void changecols(int);	//update the column
	void level1();			//level 1 program
	void printchess(bool);	//print the chess board
	bool checkmove(int,int);//check if the move is viable
	void initializeboard(int);//initialize the board in levels 3-4
	void dijkstra();		//the optimal path finder program
	void swapboard(int,int);//swap 2 elements in the board
	~chess(){if (moveson){delete []moves;}if(boardon){delete board;}}//destructor
	bool checkreachability(int,int);//check if the knight can make it to the other block
	int fetch(int r,int c);	//find the index that has the row r and column c
	void printpath();		//prints the path
	void initializehardboard(int);//initializes the board for the longest path problem
	bool checkreach(int,int);//checks if the block can be reached
	void initialize(int* steps,int* values,int n);//some initializations for level 5
	void level5();			//Level 5!
	bool checkval(int *values,int cur,int n);//Checks if the knight was on the block before
};