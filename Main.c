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
}slots2;
int main()
{ 
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
	getDesiredElement(7, &row,&column);
	if(row >= 7/2)
	{
		if(column >= 7/2)
			{
				currSlot = reachDesiredElement(row,column,downRight);
			}
		else
		{
			currSlot = reachDesiredElement(row,column,downLeft);
		}
	}
	else
	{
		if(column >= 7/2)
			{
				currSlot = reachDesiredElement(row,column, upRight);
			}
		else 
			{
				currSlot = reachDesiredElement(row,column,upLeft);
			}
	}
	for(int i=0; i<7; i++){
		for(int j=0; j<7;j++){
			explored[i][j] = false;
		}
	}

	foundSlots = malloc(7*7*sizeof(struct slots));
	printf("\n\nFunction findSlotsinvoked:\n");

	if(currSlot!= NULL)
	{
		//invokes function findSlots. The required distance is a constant
		//However you can reuse this function providing as input any arbitrary distance
		findSlots(3, 0, currSlot, foundSlots, &count, explored);
		for(int i=0; i<count; i++)
		{
			printf("(%d, %d)-> ",foundSlots[i].row, foundSlots[i].column);
		}
	}

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
	assignplayer(&board);
}
void assignplayer(struct slots ***board)
{
	int input=0;
	printf("Please input  number of players 2-6\n"); // asking the user to input a set of players (max 6). 
   	scanf ("%d", &input);
   	while (input <2 || input > 6)
	{
   		printf("Input is invaid, Please input  number of players 2-6\n");
   		scanf ("%d", &input);
    }	
    struct slots2 *players = malloc(input * sizeof(struct slots2));
    for(int i=0;i<input;i++)
    { 
    	printf("Please input name and type for player %d\n", i+1);
		scanf("%s%s", &players[i].name,&players[i].type);
		if(players[i].type[0]=='O' || players[i].type[0]=='o') //checking for the type of the player, and accordingly assigning values
		{
			players[i].magicskills=0;
			players[i].smartness=rand()%20;
			players[i].luck=rand()%(50-players[i].smartness);
			players[i].strength=rand()%(100+1-80)+80;
			players[i].dexterity=rand()%(100+1-80)+80;
		}
		if(players[i].type[0]=='H' || players[i].type[0]=='h') //checking for the type of the player, and accordingly assigning values
		{   do {
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
			players[i].magicskills=rand()%(80+1-50)+50;
			players[i].smartness=rand()%(100+1-70)+70;
			players[i].luck=rand()%(100+1-60)+60;
			players[i].strength=rand()%51;
			players[i].dexterity=rand()%100;
		}
		if(players[i].type[0]=='W' || players[i].type[0]=='w') //checking for the type of the player, and accordingly assigning values
		{
			players[i].magicskills=rand()%(100+1-80)+80;
			players[i].smartness=rand()%(100+1-90)+90;
			players[i].luck=rand()%(100+1-50)+50;
			players[i].strength=rand()%21;
			players[i].dexterity=rand()%100;
		}
   		int r=rand()%7; int c=rand()%7;
   		players[i].rowvalue=r;
   		players[i].columnvalue=c;
   	}
   	
   }
   void getDesiredElement(int boardSize, int *row, int *col)
{
	printf("Please enter the column and the Row of the desired slot \n");
	printf("Note that size of the board is %d\n", boardSize);

		//it will cycle asking the user to insert the row
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Row: ");
			scanf("%d", row);
			printf("%d\n", *row);
			if(row < 0 && *row >= boardSize)
				printf("Error: Incorrect row dimension\n");
		} while(*row<0 && *row>=boardSize);

		//it will cycle asking the user to insert the column
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Column: ");
			scanf("%d", col);
			printf("%d\n", *col);
			if(*col<0 && *col>=boardSize)
				printf("Error: Incorrect column dimension\n");
		} while(*col<0 && *col>=boardSize);
}
  struct slots* reachDesiredElement(int row, int column, struct slots *initialSlot)
  {

	bool found = false;
	//current slot
	struct slots *currentSlot = initialSlot;

	printf("\nFunction reachDesiredElement invoked\n");

	//prints the column and the row of the initial slotsfrom which the search starts
	printf("Initial slots(%d, %d) -> \n",initialSlot->row,initialSlot->column);


	//while the slotsis not found
	while(found==false)
	{


		//if the row of the current slotsis > of the row of the desired slot,
		//we move up
		if(currentSlot->row > row)
		{
			//the current slotsnow points to the slotsone row up
			currentSlot = currentSlot->up;
			//prints the column and the row of the current slot
			printf("Current slots(%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}
		//if the row of the current slotsis < of the row of the desired slot,
		//we move down
		if(currentSlot->row < row)
		{
			//the current slotsnow points to the slotsone row down
			currentSlot = currentSlot->down;
			//prints the row and the column of the current slot
			printf("Current slots(%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the column of the current slotsis > of the column of the desired slot,
		//we move left
		if(currentSlot->column > column)
		{

			//the current slotsnow points to the slotsone column left
			currentSlot = currentSlot->left;
			//prints the row and the column of the current slot
			printf("Current slots(%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}

		//if the column of the current slotsis < of the column of the desired slot,
		//we move right
		if(currentSlot->column < column)
		{

			//the current slotsnow points to the slotsone column right
			currentSlot = currentSlot->right;
			//prints the row and the column of the current slot
			printf("Current slots(%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the current slotsis at a column and a row equal to the desired column and row, respectively
		// we found the slot
		if(currentSlot->column == column && currentSlot->row == row){
			printf("Found\n");
			found = true;

		}

	}
	//returns the found slot
	move(&currentSlot);
	return currentSlot;
}
void currentSlot(*current)
{   
	int opt=0;
	if(current->up==NULL && current->left==NULL && current->right!=NULL && current->down!=NULL)
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
				current=current->right;
			}
			if(opt==4)
			{
				current=current->down;
			}
		}
	}
	if(current->up==NULL && current->right==NULL && current->left!=NULL && current->down!=NULL)
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
				current=current->left;
			}
			if(opt==4)
			{
				current=current->down;
			}
		}
	}
	if(current->up!=NULL && current->right==NULL && current->left!=NULL && current->down==NULL)
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
				current=current->left;
			}
			if(opt==2)
			{
				current=current->up;
			}
		}
	}
	if(current->up!=NULL && current->right!=NULL && current->left==NULL && current->down==NULL)
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
				current=current->right;
			}
			if(opt==2)
			{
				current=current->up;
			}
		}
	}
	if(current->up==NULL && current->right!=NULL && current->left!=NULL && current->down!=NULL)
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
				current=current->left;
			}
			if(opt==4)
			{
				current=current->down;
			}
			if(opt==1)
			{
				current=current->right;
			}
		}
	}
	if(current->up!=NULL && current->right==NULL && current->left!=NULL && current->down!=NULL)
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
				current=current->left;
			}
			if(opt==4)
			{
				current=current->down;
			}
			if(opt==2)
			{
				current=current->up;
			}
		}
	}
	if(current->up!=NULL && current->right!=NULL && current->left!=NULL && current->down==NULL)
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
				current=current->left;
			}
			if(opt==2)
			{
				current=current->up;
			}
			if(opt==1)
			{
				current=current->right;
			}
		}
	}
	if(current->up!=NULL && current->right!=NULL && current->left==NULL && current->down!=NULL)
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
				current=current->down;
			}
			if(opt==2)
			{
				current=current->up;
			}
			if(opt==1)
			{
				current=current->right;
			}
		}
	}
	if(current->up!=NULL && current->right!=NULL && current->left!=NULL && current->down!=NULL)
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
				current=current->down;
			}
			if(opt==2)
			{
				current=current->up;
			}
			if(opt==1)
			{
				current=current->right;
			}
			if(opt==3)
			{
				current=current->left;
			}
		}
	}
		
	   



 
   	
    	
