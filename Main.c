#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
enum slotname {ground, hill, city}; //using enumerators for better readability
typedef struct slots
{
int row;
int column;
int slotType;
struct slots *left;
struct slots *right;
struct slots *up;
struct slots *down;
}slots;
typedef struct slots2
{
char name[20];
char type[6];
double life;
int smartness;
int strength;
int magicskills;
int luck;
int dexterity;
int status;
struct slots *playerposition;
}slots2;
void createBoard( struct slots **upLeft, struct slots **upRight, struct slots **downLeft, struct slots **downRight);//creates the 7*7 board using the linked list
struct slots2 * assignplayer(int input, struct slots2 *players);//function to assign the names, type, and all the capabilities to each player
struct slots2 * move(struct slots2 *players2); //function to enable the player to move up,right,left, or down.
int main()
{ 
	struct slots2 *player3;
	int row, column;
	struct slots *currSlot = NULL;
	struct slots *foundSlots;
	bool explored[7][7];
	int count =0;
	//pointer to slots(0,0)
	struct slots *upLeft;
	//pointer to slots(0,boardSize -1)
	struct slots *upRight;
	//pointer to slots(boardSize - 1, 0)
	struct slots *downLeft;
	//pointer to slots(boardSize - 1, boardSize -1)
	struct slots *downRight;
	createBoard(&upLeft, &upRight, &downLeft, &downRight);
	printf("Enter the number of players:\n");
	int x=0;
	scanf("%d",&x);
	while (x <2 || x > 6)
	{
   		printf("Input is invaid, please input  number of players 2-6\n");
   		scanf ("%d", &x);
    }
	struct slots2 *players= assignplayer(x, &player3);
	for(int i=0;i<x;i++)
	{
		players[i].status=1;
	}
	
	int option=0; int counter=0;
	do
	{
		counter=0;
		for(int j=0;j<x;j++)
		{
			if(players[j].status==1)
			{
				counter++;
			}
		}
		for(int i=0;i<x;i++)
		{
			if(players[i].status==1)
			{
				printf("Player %d Enter 1 to move or 2 to attack, 0 to exit:\n",i+1);
				scanf("%d",&option);
				if(option==1)
				{
					move(&players[i]);
				}
				if(option==0)
				{
					players[i].status=0;
				}
			}
		}
	} while(counter>1);
				
		
	return 0;
}
void createBoard( struct slots **upLeft, struct slots **upRight, struct slots **downLeft, struct slots **downRight)
{

	//The board is represented as a pointer of pointer to slots
	//This allocates in memory the space for the pointers to each row of the board
	struct slots **board = malloc(7 * sizeof(struct slots));


	for(int i=0;i<7;i++)
	{
		//This allocates in memory the space for the slots in each row of the board
		board[i]=malloc(7 * sizeof(struct slots));

		//For each slotsit sets up the row and column number
		for(int j=0;j<7;j++)
		{
			board[i][j].row =i;
			board[i][j].column =j;
			int v=rand()%3;
			board[i][j].slotType=v;
		}
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i=1;i<6;i++)
	{
		for(int j=1;j<6;j++)
		{
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	//
	for(int j=1;j<6;j++)
	{
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[6][j].right = &board[6][j+1];
		board[6][j].left = &board[6][j-1];
		board[6][j].up = &board[5][j];
		board[6][j].down = NULL;
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	//
	for(int i = 1; i <6; i++)
	{
		//It sets up the adjacent slots for the slots that are in the first column.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		//It sets up the adjacent slots for the slots that are in the last column.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][6].left = &board[i][5];
		board[i][6].up = &board[i -1][6];
		board[i][6].down = &board[i+1][6];
		board[i][6].right = NULL;
	}


		//It sets up the adjacent slots for the slotsat position (0,0).
		//This only has only 2 adjacent slots: right and down
		board[0][0].right = &board[0][1];
		board[0][0].down = &board[1][0];

		//It sets up the adjacent slots for the slotsat position (0,boardSize -1).
		//This only has only 2 adjacent slots: left and down
		board[0][6].left = &board[0][5];
		board[0][6].down = &board[1][6];

		//It sets up the adjacent slots for the slotsat position (boarSize -1 ,0).
		//This only has only 2 adjacent slots: up and right
		board[6][0].right = &board[6][1];
		board[6][0].up = &board[5][0];

		//It sets up the adjacent slots for the slotsat position (boarSize -1 ,boardSize-1).
		//This only has only 2 adjacent slots: up and left
		board[6][6].up=&board[5][6];
		board[6][6].left=&board[5][5];







	//assigns a pointer to slotsat position (0, 0)
	*upLeft = &board[0][0];
	//assigns pointer of pointer to slotsat position (0, boardSize -1)
	*upRight = &board[0][6];
	//assigns pointer of pointer to slotsat position ( boardSize -1,)
	*downLeft = &board[6][0];
	//assigns pointer of pointer to slotsat position (boardSize -1, boardSize -1)
	*downRight = &board[6][6];
}
struct slots2 * assignplayer(int input, struct slots2 *players)
{
     players=malloc(input*sizeof(struct slots2));
    
    for(int i=0;i<input;i++)
    {   
    	printf("Please input name and type for player %d\n", i+1);
		scanf("%s%s", players[i].name,players[i].type);
		printf("Hello");
		if(players[i].type[0]=='O' || players[i].type[0]=='o') //checking for the type of the player, and accordingly assigning values
		{
			players[i].life=100;
			players[i].magicskills=0;
			players[i].smartness=rand()%20;
			players[i].luck=rand()%(50-players[i].smartness);
			players[i].strength=rand()%(100+1-80)+80;
			players[i].dexterity=rand()%(100+1-80)+80;
		}
		if(players[i].type[0]=='H' || players[i].type[0]=='h') //checking for the type of the player, and accordingly assigning values
		{   do {
			players[i].life=100;
			players[i].magicskills=rand()%300;
			players[i].smartness=rand()%(300-players[i].magicskills);
			players[i].luck=rand()%(300-(players[i].magicskills+players[i].smartness));
			players[i].strength=rand()%(300-(players[i].magicskills+players[i].smartness+players[i].luck));
			players[i].dexterity=rand()%(300-(players[i].magicskills+players[i].smartness+players[i].luck+players[i].strength));
		    }
		    while(players[i].magicskills>100 || players[i].smartness>100 || players[i].luck>100 || players[i].strength>100 || players[i].dexterity>100);
		}
		if(players[i].type[0]=='E' || players[i].type[0]=='e') //checking for the type of the player, and accordingly assigning values
		{
			players[i].life=100;
			players[i].magicskills=rand()%(80+1-50)+50;
			players[i].smartness=rand()%(100+1-70)+70;
			players[i].luck=rand()%(100+1-60)+60;
			players[i].strength=rand()%51;
			players[i].dexterity=rand()%100;
		}
		if(players[i].type[0]=='W' || players[i].type[0]=='w') //checking for the type of the player, and accordingly assigning values
		{
			players[i].life=100;
			players[i].magicskills=rand()%(100+1-80)+80;
			players[i].smartness=rand()%(100+1-90)+90;
			players[i].luck=rand()%(100+1-50)+50;
			players[i].strength=rand()%21;
			players[i].dexterity=rand()%100;
		}
   		int r=rand()%7; int c=rand()%7;
   		players[i].playerposition->row=r;
   		players[i].playerposition->column=c;
   	}
   	return players;
   }
struct slots2 * move(struct slots2 *players2)
{
	int opt=0;
	if(players2->playerposition->up==NULL && players2->playerposition->left==NULL && players2->playerposition->right!=NULL && players2->playerposition->down!=NULL)
	{
		printf("Enter 1 to move right, 4 to move down:\n");
		scanf("%d",&opt);
		if(opt!=1 && opt!=4)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==1)
			{
				players2->playerposition=players2->playerposition->right;
			}
			if(opt==4)
			{
				players2->playerposition=players2->playerposition->down;
			}
		}
	}
	if(players2->playerposition->up==NULL && players2->playerposition->right==NULL && players2->playerposition->left!=NULL && players2->playerposition->down!=NULL)
	{
		printf("Enter 3 to move left, 4 to move down:\n");
		scanf("%d",&opt);
		if(opt!=3 && opt!=4)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==3)
			{
				players2->playerposition=players2->playerposition->left;
			}
			if(opt==4)
			{
				players2->playerposition=players2->playerposition->down;
			}
		}
	}
	if(players2->playerposition->up!=NULL && players2->playerposition->right==NULL && players2->playerposition->left!=NULL && players2->playerposition->down==NULL)
	{
		printf("Enter 3 to move left, 2 to move up:\n");
		scanf("%d",&opt);
		if(opt!=3 && opt!=2)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==3)
			{
				players2->playerposition=players2->playerposition->left;
			}
			if(opt==2)
			{
				players2->playerposition=players2->playerposition->up;
			}
		}
	}
	if(players2->playerposition->up!=NULL && players2->playerposition->right!=NULL && players2->playerposition->left==NULL && players2->playerposition->down==NULL)
	{
		printf("Enter 1 to move right, 2 to move up:\n");
		scanf("%d",&opt);
		if(opt!=1 && opt!=2)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==1)
			{
				players2->playerposition=players2->playerposition->right;
			}
			if(opt==2)
			{
				players2->playerposition=players2->playerposition->up;
			}
		}
	}
	if(players2->playerposition->up==NULL && players2->playerposition->right!=NULL && players2->playerposition->left!=NULL && players2->playerposition->down!=NULL)
	{
		printf("Enter 3 to move left, 1 to move right, 4 to move down:\n");
		scanf("%d",&opt);
		if(opt!=3 && opt!=4 && opt!=1)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==3)
			{
				players2->playerposition=players2->playerposition->left;
			}
			if(opt==4)
			{
				players2->playerposition=players2->playerposition->down;
			}
			if(opt==1)
			{
				players2->playerposition=players2->playerposition->right;
			}
		}
	}
	if(players2->playerposition->up!=NULL && players2->playerposition->right==NULL && players2->playerposition->left!=NULL && players2->playerposition->down!=NULL)
	{
		printf("Enter 3 to move left, 2 to move up, 4 to move down:\n");
		scanf("%d",&opt);
		if(opt!=3 && opt!=4 && opt!=2)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==3)
			{
				players2->playerposition=players2->playerposition->left;
			}
			if(opt==4)
			{
				players2->playerposition=players2->playerposition->down;
			}
			if(opt==2)
			{
				players2->playerposition=players2->playerposition->up;
			}
		}
	}
	if(players2->playerposition->up!=NULL && players2->playerposition->right!=NULL && players2->playerposition->left!=NULL && players2->playerposition->down==NULL)
	{
		printf("Enter 3 to move left, 1 to move right, 2 to move up:\n");
		scanf("%d",&opt);
		if(opt!=3 && opt!=2 && opt!=1)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==3)
			{
				players2->playerposition=players2->playerposition->left;
			}
			if(opt==2)
			{
				players2->playerposition=players2->playerposition->up;
			}
			if(opt==1)
			{
				players2->playerposition=players2->playerposition->right;
			}
		}
	}
	if(players2->playerposition->up!=NULL && players2->playerposition->right!=NULL && players2->playerposition->left==NULL && players2->playerposition->down!=NULL)
	{
		printf("Enter 4 to move down, 1 to move right, 2 to move up:\n");
		scanf("%d",&opt);
		if(opt!=4 && opt!=2 && opt!=1)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==4)
			{
				players2->playerposition=players2->playerposition->down;
			}
			if(opt==2)
			{
				players2->playerposition=players2->playerposition->up;
			}
			if(opt==1)
			{
				players2->playerposition=players2->playerposition->right;
			}
		}
	}
	if(players2->playerposition->up!=NULL && players2->playerposition->right!=NULL && players2->playerposition->left!=NULL && players2->playerposition->down!=NULL)
	{
		printf("Enter 4 to move down, 1 to move right, 2 to move up, 3 to move left:\n");
		scanf("%d",&opt);
		if(opt!=4 && opt!=2 && opt!=1 && opt!=3)
		{
			printf("Invalid Input\n");
		}
		else
		{
			if(opt==4)
			{
				players2->playerposition=players2->playerposition->down;
			}
			if(opt==2)
			{
				players2->playerposition=players2->playerposition->up;
			}
			if(opt==1)
			{
				players2->playerposition=players2->playerposition->right;
			}
			if(opt==3)
			{
				players2->playerposition=players2->playerposition->left;
			}
		}
	}
	return 0;
}
		
	   



 
   	
    	
