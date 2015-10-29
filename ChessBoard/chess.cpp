#include "chess.hpp"

chess::chess(int s,int lvl)
{
	visited=0;
	count=0;
	size=s;
	moveson=false;
	boardon=false;
	if(lvl==2||lvl==3){initializeboard(lvl);}
	else if (lvl==5){initializehardboard(s);}
}

void chess::changerows(int r)
{
	moves[count][0]=r;
}

void chess::changecols(int c)
{
	moves[count][1]=c;
	count++;
}

void chess::level1()
{
	moveson=true;
	while(true){
			try{moves=new int *[size*size];break;}
			catch(bad_alloc){continue;}}
	int i=0;
	
	for(i=0;i<size*size;i++)
	{
		while(true){
			try{moves[i]=new int [2];break;}
			catch(bad_alloc){continue;}}
	}
	
	
	cout<<"Please input the coordinates of your initial position!\n";
	
	changerows(parser::inputint("row",size,false));
	changecols(parser::inputint("column",size,false));
	
	cout<<"Would you like to get your feedback and print your output after each step? Enter y for yes and n for no:\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input=="y"){printing=true;break;}
		if (input=="n"){printing=false;break;}
		if (input=="quit"){exit(0);}
		cout<<"Invalid input try again!\n";
	}
	cout<<"Please input the respective row and column values of the next steps. When you are done please enter end.\n";
	
	while (true)
	{
		cout<<"New move\n";
		int r,c;
		r=parser::inputint("row",size,true);
		if (r==-1){break;}
		c=parser::inputint("column",size,true);
		if (c==-1){break;}
		changerows(r);
		changecols(c);
		if(printing)
		{
			if(checkmove(count-1,count-2))
				{
					printchess(false);
				}
			else
			{
				cout<<"Invalid move!\n";
				count--;
			}
		}
		
	}
	if(printing==false)
	{
		int i;
		for(i=0;i<count-1;i++)
		{
			if(checkmove(i,i+1)==false)
			{
				cout<<"The moves are wrong!\n";
				break;
			}
			if (i==count-2)
			{
				cout<<"The moves are right!\n";
				printchess(true);
			}
		}
	}
}

void chess::printchess(bool fin)
{
	int i=0;
	int j=0;
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(i==moves[0][0]&&j==moves[0][1])
			{cout<<"S\t";}
			else if(i==moves[count-1][0]&&j==moves[count-1][1])
			{if(fin){cout<<"E\t";}
			else{cout<<"K\t";}}
			else
			{cout<<".\t";}
		}
		cout<<endl;
	}
}

bool chess::checkmove(int a,int b)
{
	if((moves[a][0]-moves[b][0])*(moves[a][1]-moves[b][1])==2||(moves[a][0]-moves[b][0])*(moves[a][1]-moves[b][1])==-2)
	{
		return true;
	}
	else
		{return false;}
}

void chess::initializeboard(int lvl)
{
	boardon=true;
	int i;
	while(true)
		{
			try{board=new int *[size*size];break;}
			catch(bad_alloc){continue;}
		}
	
	for(i=0;i<size*size;i++)
	{
		while(true){
			try{board[i]=new int [7];break;}
			catch(bad_alloc){continue;}}
	}
	
	int r=0;
	int c=0;
	
	for(i=0;i<size*size;i++)
	{
		if(i%size==0&&i>0)
		{
			r++;
			c=0;
		}
		board[i][0]=r;
		board[i][1]=c;
		c++;
		board[i][2]=10000; //initialize cost to a big value
		board[i][4]=10000;
		board[i][5]=10000;
		board[i][6]=0;
	}
	string line;
	char bla [13];
	sprintf(bla,"chess%d.txt",lvl);
	
	ifstream myfile(bla);
	
	if (myfile.is_open())  //read the text files to log in the conditions on different blocks
  {
	i=0;
    while ( getline (myfile,line) )
    {
		int j;
		for(j=0;j<line.length();j++)
		{
			if(line[j]=='.')
			{
				board[i][3]=0;
				i++;
			}
			else if(line[j]=='W')
			{
				board[i][3]=1;
				i++;
			}
			else if(line[j]=='R')
			{
				board[i][3]=2;
				i++;
			}
			else if(line[j]=='B')
			{
				board[i][3]=3;
				i++;
			}
			else if(line[j]=='T')
			{
				board[i][3]=4;
				i++;
			}
			else if(line[j]=='L')
			{
			board[i][3]=5;
			i++;
		}
	  }
	}
    myfile.close();
  }
  
}

void chess::swapboard(int a,int b)
{
	if(a==b){return;}
	int temp;
	int i=0;
	for(i=0;i<7;i++)
	{
		temp=board[a][i];
		board[a][i]=board[b][i];
		board[b][i]=temp;
	}
}

void chess::dijkstra()
{
	int cost=0;
	
	int ro,co;
	int in;
	
	cout<<"Please input the coordinates of your initial position!\n";
	while(true)
	{
		ro=(parser::inputint("row",size,false));
		co=(parser::inputint("column",size,false));
		in=ro*size+co;
		if(board[fetch(ro,co)][3]!=2||board[fetch(ro,co)][3]!=3){swapboard(0,in);board[0][2]=0;break;} 
		else {cout<<"This spot is reserved!\n";} 
	}
	
	cout<<"Please input the coordinates of your final position!\n";
	while(true)
	{
		
		ro=(parser::inputint("row",size,false));
		co=(parser::inputint("column",size,false));
		
		if(ro==board[0][0]&&board[0][1]==co)
		{
			cout<<"U picked the same spot as the initial position!\n";
			continue;
		}
		
		if(board[fetch(ro,co)][3]!=2||board[fetch(ro,co)][3]!=3){swapboard(size*size-1,(ro==0&&co==0)? in:ro*size+co);break;} 
		else {cout<<"This spot is reserved!\n";} 
	}
	
	while(true)
	{
		bool done=false;
		int i;
		for(i=visited+1;i<size*size;i++)
		{
			if((board[i][0]-board[visited][0])*(board[i][1]-board[visited][1])==2||(board[i][0]-board[visited][0])*(board[i][1]-board[visited][1])==-2)
			{
				if(checkreachability(visited,i)==false){continue;}
				if(i==size*size-1) //connected to the target, we are done
				{
					board[i][2]=board[visited][2]+1;
					board[i][4]=board[visited][0];
					board[i][5]=board[visited][1];
					board[i][6]=board[visited][6]+1;
					done=true;
					break;
				}
				
				if (board[i][3]==0) //In case there is no condition
				{
					cost=board[visited][2]+1;
					if(cost<board[i][2])
					{
						board[i][2]=cost;
						board[i][4]=board[visited][0];
						board[i][5]=board[visited][1];
						board[i][6]=board[visited][6]+1;
					}
				}
				else if (board[i][3]==1) //In case there is Water
				{
					cost=board[visited][2]+2;
					if(cost<board[i][2])
					{
						board[i][2]=cost;
						board[i][4]=board[visited][0];
						board[i][5]=board[visited][1];
						board[i][6]=board[visited][6]+1;
					}
				}
				else if (board[i][3]==5) //In case there is Lava
				{
					cost=board[visited][2]+5;
					if(cost<board[i][2])
					{
						board[i][2]=cost;
						board[i][4]=board[visited][0];
						board[i][5]=board[visited][1];
						board[i][6]=board[visited][6]+1;
					}
				}
				else if(board[i][3]==4) //In case it is a teleport update all instances
				{
					cost=board[visited][2]+1;
					if(cost<board[i][2])
					{
						int j;
						for(j=visited+1;j<size*size;j++)
						{
							if(board[j][3]==4)
							{
								board[j][2]=cost;
								board[j][4]=board[visited][0];
								board[j][5]=board[visited][1];
								board[j][6]=board[visited][6]+1;
							}
						}
					}
				}
			}
		}
		if(done){break;}
		visited++;
		
		if(visited>size*size-2){break;}
		
		int min=10000;
		int mini;
		for(i=visited;i<size*size;i++)
		{
			if(board[i][2]<min)
			{
				min=board[i][2];
				mini=i;
			}
		}
		swapboard(visited,mini);
	}
	printpath();
	
}

bool chess::checkreachability(int a,int b) 
{
	bool t1=true;
	bool t2=true;
	if (board[b][3]==3||board[b][3]==2) //if it is a rock or wall
	{
		return false;
	}
	
	if((board[b][0]-board[a][0])/2==0)
	{
		if(board[fetch(board[b][0],board[a][1])][3]==3)
		{
			t1=false;
		}
		else if(board[fetch(board[b][0],(board[b][1]+board[a][1])/2)][3]==3)
		{
			t1=false;
		}
		if(board[fetch(board[a][0],(board[b][1]+board[a][1])/2)][3]==3)
		{
			t2=false;
		}
		else if(board[fetch(board[a][0],board[b][1])][3]==3)
		{
			t2=false;
		}
	}
	else if((board[b][1]-board[a][1])/2==0)
	{
		if(board[fetch(board[a][0],board[b][1])][3]==3)
		{
			t1=false;
		}
		else if(board[fetch((board[b][0]+board[a][0])/2,board[b][1])][3]==3)
		{
			t1=false;
		}
		if(board[fetch((board[b][0]+board[a][0])/2,board[a][1])][3]==3)
		{
			t2=false;
		}
		else if(board[fetch(board[b][0],board[a][1])][3]==3)
		{
			t2=false;
		}
	}
	if(t1==false&&t2==false){return false;}
	else{return true;}
}


int chess::fetch(int r,int c) 
{
	int i;
	for(i=0;i<size*size;i++)
	{
		if(board[i][0]==r&&board[i][1]==c)return i;
	}
}

void chess::initializehardboard(int s)
{
	size=s;
	
	boardon=true;
	int i;
	while(true)
		{
			try{board=new int *[size*size];break;}
			catch(bad_alloc){continue;}
		}
	
	for(i=0;i<size*size;i++)
	{
		while(true){
			try{board[i]=new int [11];break;}
			catch(bad_alloc){continue;}}
	}
	
	int r=0;int c=0;
	for(i=0;i<size*size;i++)
	{
		if(i%size==0&&i!=0)
		{
			r++;
			c=0;
		}
		board[i][0]=r;
		board[i][1]=c;
		board[i][2]=0;
		c++;
		int k;
		for(k=3;k<11;k++)
		{
			board[i][k]=-1;
		} 
	}
	int j;
	
	for(i=0;i<size*size;i++)
	{
		for(j=0;j<size*size;j++)
		{
			if(checkreach(i,j))
			{
				board[i][2]=board[i][2]+1;
				board[i][board[i][2]+2]=j;
			}
		}
	}
}

void chess::printpath()
{
	int path[board[size*size-1][6]+1][2];
	cout<<"\nThe optimal path from the initial to the final position will be:"<<endl;
	int r=board[size*size-1][0];
	int c=board[size*size-1][1];
	
	int i=0;
	
	path[board[size*size-1][6]][0]=board[0][0];
	path[board[size*size-1][6]][1]=board[0][1];
	
	while(true)
	{
		path[i][0]=r;
		path[i][1]=c;
		
		i++;
		
		if(r==board[0][0]&&c==board[0][1]){break;}
		
		int j;
		for(j=0;j<size*size;j++)
		{
			if (board[j][0]==r&&board[j][1]==c)
			{
				r=board[j][4];c=board[j][5];
			}
		}
	}
	
	for(i=board[size*size-1][6];i>-1;i--)
	{
		cout<<path[i][0]<<","<<path[i][1]<<endl;
	}
}

bool chess::checkreach(int a,int b)
{
	if((board[a][0]-board[b][0])*(board[a][1]-board[b][1])==2||(board[a][0]-board[b][0])*(board[a][1]-board[b][1])==-2)
	{
		return true;
	}
	else
		{return false;}
}

void chess::level5()
{
	int ip,fp;
	cout<<"Please input the index of your initial position!\nThe indexes go from left to right. Example (5 sized board):\n 0  1  2  3  4\n 5  6  7  8  9\n10 11 12 13 14\n15 16 17 18 19\n";
	
	ip=(parser::inputint("index",size*size,false));
	
	cout<<"Please input the index of your final position!\n";
	while(true)
	{
		fp=(parser::inputint("index",size*size,false));
		if(fp==ip)
		{
			cout<<"U picked the same spot as the initial position!\n";
			continue;
		}
		break;
	}
	
	int steps[size*size];
	int values[size*size];
	int maxval[size*size];
	int maxmoves=0;
	count=0;
	initialize(steps,values,size*size);
	int bla=0;
	values[0]=ip;
	
	while(true)
	{ 
		if(values[count]==fp)
		{
			if (maxmoves<count)
			{
				maxmoves=count;
				int i;
				for(i=0;i<size*size;i++)
				{
					maxval[i]=values[i];
				}
				if(maxmoves==size*size-1){break;}
			}
		}
		
		if(steps[count]+1<board[values[count]][2])
		{
			steps[count]++;
			if(checkval(values,board[values[count]][3+steps[count]],count+1))
			{
				count++;
				values[count]=board[values[count-1]][3+steps[count-1]];
			}
		}
		else
		{
			if(count==0){break;}
			steps[count]=-1;
			count--;
		}
	}
	int i=0;
	cout<<"The longest path given by index is:\n";
	while(true)
	{
		cout<<maxval[i]<<endl;
		if(maxval[i]==fp){break;}
		i++;
	}
}

void chess::initialize(int* steps,int* values,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		steps[i]=-1;
		values[i]=-1;
	}
}

bool chess::checkval(int *values,int cur,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(values[i]==cur)
		{
			return false;
		}
	}
	return true;
}