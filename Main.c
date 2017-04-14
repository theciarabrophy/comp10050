#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

enum SlotType {
    Ground,
    Hill,
    City
}; //using enumerators for better readability

typedef struct Slot {
    int row;
    int column;
    enum SlotType slotType;
    struct Slot *left;
    struct Slot *right;
    struct Slot *up;
    struct Slot *down;
} Slot;

typedef struct Player {
    char name[20];
    char type[6];
    double life;
    int smartness;
    int strength;
    int magicskills;
    int luck;
    int dexterity;
    int status;
    struct Slot *playerposition;
} Player;

void createBoard(int n); //creates the 7*7 board using the linked list
void assignPlayer(int noOfPlayers); //function to assign the names, type, and all the capabilities to each player
void move(struct Player *players2); //function to enable the player to move up,right,left, or down.
Slot* getSlot(int r, int c);
void printfunction(struct Player players3);
struct Slot *_slot;
struct Player *_players;
const int N = 7;

int main() {
    createBoard(N);
    printf("Enter the number of players:\n");
    int noOfPlayers = 0;
    scanf("%d", &noOfPlayers);
    while (noOfPlayers < 2 || noOfPlayers > 6) {
        printf("Input is invaid, please input  number of players 2-6\n");
        scanf("%d", &noOfPlayers);
    }
    assignPlayer(noOfPlayers);
    struct Slot *leftMost = _slot;
    for (int i = 0; i < N; i++) {
        struct Slot *curr = leftMost;
        for (int j = 0; j < N; j++) {
            printf("%d ", curr->row);
            if (curr->right != NULL) {
                curr = curr->right;
            }
        }
        printf("\n");
        if (leftMost->down != NULL) {
            leftMost = leftMost->down;
        }
    }
    return 0;
}

void createBoard(int n) {

    _slot = malloc(sizeof (Slot));

    Slot *start = _slot;
    Slot *curr = start;
    for (int i = 1; i < n; i++) {
        Slot *next = malloc(sizeof (Slot));
        Slot *previous = malloc(sizeof (Slot));
        curr->right = next;
        
        if(i>1)
        {
        	curr->left= previous;
        }
        curr = curr->right;
    }

    Slot *top = _slot;
    for (int j = 1; j < n; j++) 
    {
        Slot *down = malloc(sizeof (Slot));

        Slot *currUp = top;
        Slot *currDown = down;
        for (int i = 1; i < n; i++) 
        {
            Slot *next = malloc(sizeof (Slot));
            Slot *previous = malloc(sizeof (Slot));
            currDown->right = next;
            currDown->up = currUp;
            currUp->down = currDown;
            if(i>1)
            {
            	currDown->left=previous;
            }
            currUp = currUp->right;
            currDown = currDown->right;
        }
        top = down;
    }

    struct Slot *leftMost = _slot;
    for (int i = 0; i < n; i++) 
    {
        struct Slot *curr = leftMost;
        for (int j = 0; j < n; j++) 
        {
            curr->row = i;
            curr->column = j;
            curr->slotType = rand() % 3;
            if (curr->right != NULL)
             {
                curr = curr->right;
            }
        }
        if (leftMost->down != NULL) 
        {
            leftMost = leftMost->down;
        }
    }
}

void assignPlayer(int noOfPlayers) 
{   srand(time(NULL));
    _players = malloc(noOfPlayers * sizeof (Player));
    Player *players = _players;
    for (int i = 0; i < noOfPlayers; i++) 
    {
        printf("Please input name and type for player %d:\n", i + 1);
        scanf("%s %s", players[i].name, players[i].type);
        if (players[i].type[0] == 'O' || players[i].type[0] == 'o') //checking for the type of the player, and accordingly assigning values
        {
            players[i].life = 100;
            players[i].magicskills = 0;
            players[i].smartness = rand() % 20;
            players[i].luck = rand() % (50 - players[i].smartness);
            players[i].strength = rand() % (100 + 1 - 80) + 80;
            players[i].dexterity = rand() % (100 + 1 - 80) + 80;
        }
        if (players[i].type[0] == 'H' || players[i].type[0] == 'h') //checking for the type of the player, and accordingly assigning values
        {
            do {
                players[i].life = 100;
                players[i].magicskills = rand() % 300;
                players[i].smartness = rand() % (300 - players[i].magicskills);
                players[i].luck = rand() % (300 - (players[i].magicskills + players[i].smartness));
                players[i].strength = rand() % (300 - (players[i].magicskills + players[i].smartness + players[i].luck));
                players[i].dexterity = rand() % (300 - (players[i].magicskills + players[i].smartness + players[i].luck + players[i].strength));
            } while (players[i].magicskills > 100 || players[i].smartness > 100 || players[i].luck > 100 || players[i].strength > 100 || players[i].dexterity > 100);
        }
        if (players[i].type[0] == 'E' || players[i].type[0] == 'e') //checking for the type of the player, and accordingly assigning values
        {
            players[i].life = 100;
            players[i].magicskills = rand() % (80 + 1 - 50) + 50;
            players[i].smartness = rand() % (100 + 1 - 70) + 70;
            players[i].luck = rand() % (100 + 1 - 60) + 60;
            players[i].strength = rand() % 51;
            players[i].dexterity = rand() % 100;
        }
        if (players[i].type[0] == 'W' || players[i].type[0] == 'w') //checking for the type of the player, and accordingly assigning values
        {
            players[i].life = 100;
            players[i].magicskills = rand() % (100 + 1 - 80) + 80;
            players[i].smartness = rand() % (100 + 1 - 90) + 90;
            players[i].luck = rand() % (100 + 1 - 50) + 50;
            players[i].strength = rand() % 21;
            players[i].dexterity = rand() % 100;
        }
        int r = rand() % 7;
        int c = rand() % 7;
        players[i].playerposition = getSlot(r, c);
        
    }
    for (int i = 0; i < noOfPlayers; i++)
    {
        players[i].status = 1;
    }

    int option = 0;
    int counter = 0;
    do
    {
        
        for (int i = 0; i < noOfPlayers; i++)
        {
            counter = 0;
        	for (int j = 0; j < noOfPlayers; j++)
        	{
            	if (players[j].status == 1)
            	{
                	counter++;
            	}
        	}
        	if(counter>1)
        	{
            	if (players[i].status == 1)
            	{
                	printf("Player %d Enter 1 to move or 2 to attack, 0 to exit:\n", i + 1);
                	scanf("%d", &option);
                	if (option == 1)
                	{
						move(&players[i]);
					             
					}
                	if (option == 0)
                	{
                   		 players[i].status = 0;
                	}
				            
            	}
        	}
        }
    } while (counter > 1);
    
}

Slot* getSlot(int r, int c) 
{
    struct Slot *leftMost = _slot;
    for (int i = 0; i < N; i++) 
    {
        struct Slot *curr = leftMost;
        for (int j = 0; j < N; j++) 
        {
            if (i == r && j == c) 
            {
                return curr;
            }
            if (curr->right != NULL) 
            {
                curr = curr->right;
            }
        }
        printf("\n");
        if (leftMost->down != NULL)
         {
            leftMost = leftMost->down;
        }
    }
}

void move(struct Player *players2)
{
    int opt = 0;
    if (players2->playerposition->up == NULL && players2->playerposition->left == NULL && players2->playerposition->right != NULL && players2->playerposition->down != NULL)
    {
        printf("Enter 1 to move right, 4 to move down:\n");
        scanf("%d", &opt);
        if (opt != 1 && opt != 4)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 1)
            {
                players2->playerposition = players2->playerposition->right;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 4)
            {
                players2->playerposition = players2->playerposition->down;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up == NULL && players2->playerposition->right == NULL && players2->playerposition->left != NULL && players2->playerposition->down != NULL)
    {
        printf("Enter 3 to move left, 4 to move down:\n");
        scanf("%d", &opt);
        if (opt != 3 && opt != 4)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 3)
            {
                players2->playerposition = players2->playerposition->left;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 4)
            {
                players2->playerposition = players2->playerposition->down;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
   	printfunction(*players2); return;
    }
    if (players2->playerposition->up != NULL && players2->playerposition->right == NULL && players2->playerposition->left != NULL && players2->playerposition->down == NULL)
    {
        printf("Enter 3 to move left, 2 to move up:\n");
        scanf("%d", &opt);
        if (opt != 3 && opt != 2)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 3)
            {
                players2->playerposition = players2->playerposition->left;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 2)
            {
                players2->playerposition = players2->playerposition->up;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up != NULL && players2->playerposition->right != NULL && players2->playerposition->left == NULL && players2->playerposition->down == NULL)
    {
        printf("Enter 1 to move right, 2 to move up:\n");
        scanf("%d", &opt);
        if (opt != 1 && opt != 2)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 1)
            {
                players2->playerposition = players2->playerposition->right;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 2)
            {
                players2->playerposition = players2->playerposition->up;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up == NULL && players2->playerposition->right != NULL && players2->playerposition->left != NULL && players2->playerposition->down != NULL)
    {
        printf("Enter 3 to move left, 1 to move right, 4 to move down:\n");
        scanf("%d", &opt);
        if (opt != 3 && opt != 4 && opt != 1)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 3)
            {
                players2->playerposition = players2->playerposition->left;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 4)
            {
                players2->playerposition = players2->playerposition->down;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 1)
            {
                players2->playerposition = players2->playerposition->right;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up != NULL && players2->playerposition->right == NULL && players2->playerposition->left != NULL && players2->playerposition->down != NULL)
    {
        printf("Enter 3 to move left, 2 to move up, 4 to move down:\n");
        scanf("%d", &opt);
        if (opt != 3 && opt != 4 && opt != 2)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 3)
            {
                players2->playerposition = players2->playerposition->left;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 4)
            {
                players2->playerposition = players2->playerposition->down;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 2)
            {
                players2->playerposition = players2->playerposition->up;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up != NULL && players2->playerposition->right != NULL && players2->playerposition->left != NULL && players2->playerposition->down == NULL)
    {
        printf("Enter 3 to move left, 1 to move right, 2 to move up:\n");
        scanf("%d", &opt);
        if (opt != 3 && opt != 2 && opt != 1)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 3)
            {
                players2->playerposition = players2->playerposition->left;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 2)
            {
                players2->playerposition = players2->playerposition->up;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 1)
            {
                players2->playerposition = players2->playerposition->right;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up != NULL && players2->playerposition->right != NULL && players2->playerposition->left == NULL && players2->playerposition->down != NULL)
    {
        printf("Enter 4 to move down, 1 to move right, 2 to move up:\n");
        scanf("%d", &opt);
        if (opt != 4 && opt != 2 && opt != 1)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 4)
            {
                players2->playerposition = players2->playerposition->down;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 2)
            {
                players2->playerposition = players2->playerposition->up;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 1)
            {
                players2->playerposition = players2->playerposition->right;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    printfunction(*players2); return;
    }
    if (players2->playerposition->up != NULL && players2->playerposition->right != NULL && players2->playerposition->left != NULL && players2->playerposition->down != NULL)
    {
        printf("Enter 4 to move down, 1 to move right, 2 to move up, 3 to move left:\n");
        scanf("%d", &opt);
        if (opt != 4 && opt != 2 && opt != 1 && opt != 3)
        {
            printf("Invalid Input\n");
        }
        else
        {
            if (opt == 4)
            {
                players2->playerposition = players2->playerposition->down;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 2)
            {
                players2->playerposition = players2->playerposition->up;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 1)
            {
                players2->playerposition = players2->playerposition->right;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
            if (opt == 3)
            {
                players2->playerposition = players2->playerposition->left;
                if(players2->playerposition->slotType==Hill)
                {
                	if(players2->dexterity<50)
						{
							players2->strength=players2->strength-10;
						}
						if(players2->dexterity>=60)
						{
							players2->strength=players2->strength+10;
						}
				}
				if(players2->playerposition->slotType==City)
				{
					if(players2->smartness>60)
						{
							players2->magicskills=players2->magicskills+10;
						}
				}
            }
        }
    
    printfunction(*players2); return;
    } 
}
void printfunction(struct Player players3)
{   printf("%s is ",players3.name);
	printf("on row %d and column %d\n",(players3.playerposition->row)+1,(players3.playerposition->column)+1);
	printf("Your life points are %.2lf \n",players3.life);
	printf("Your dexterity points are %d \n",players3.dexterity);
	printf("Your smartness points are %d \n",players3.smartness);
	printf("Your magic skill points are %d \n",players3.magicskills);
	printf("Your strength points are %d \n",players3.strength);
	printf("Your luck points are %d \n",players3.luck);
}
 
