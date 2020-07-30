#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void welcomeScreen();
void emptymap(int map[][60],int noOfships);
void instructions(); 
void stage(int map[][60], int noOfships);
void bomb(int row1, int col1, int map[][60], int noOfships);


int main()
{
	int level, start, bombrow, bombcol, noOfships;
	static int map[20][60] = { 0 };

	welcomeScreen(); 
	scanf("%d", &start);
	while ((start < 0) || (start > 1))
	{
		printf("Please enter a valid input: \n");
		scanf("%d", &start);
	}
	system("cls");
	while (start== 1)
	{
		instructions(); 
		scanf("%d", &level);

		while ((level != 1) && (level != 2) && (level != 3) && (level != 4))
		{
			printf("Please enter the correct level: \n");
			scanf("%d", &level);
		}
		switch (level)
		{
		case 1:
			noOfships = 80;
			break;
		case 2:
			noOfships = 40;
			break;
		case 3:
			noOfships = 20;
			break;
        case 4:
			noOfships = 10;
			break;
		}
		system("cls");
		stage(map, noOfships); 
		
		emptymap(map,noOfships); 
		

		printf("\nEnter (row 'spacebar' col) to bomb:\n");
		scanf("%d%d", &bombrow, &bombcol);
		while ((bombrow <= 0) || (bombrow > 20) || (bombcol <= 0) || (bombcol > 60))
		{
			printf("\nEnter (row 'spacebar' col) to bomb:\n");
			scanf("%d%d", &bombrow, &bombcol);
		}
		bomb(bombrow, bombcol, map, noOfships); 

		printf("Enter '1' to continue or '0' to quit game\n"); 
		scanf("%d", &start);
		while ((start < 0) || (start > 1)) 
		{
			printf("Please enter a valid input: \n");
			scanf("%d", &start);
		} 
	} 
	system("pause");
}

void welcomeScreen() 
{
	printf("Welcome to the game of Battleship.\nYour objective is to select a certain location inorder to destroy the enemy's ship.\nMay the odds ever be in your favor.");
	printf("\n");
	printf("Enter '1' to continue or '0' to quit game\n");
} 

void instructions() 
{
	printf("There are 3 levels in this game: Beginner, Intermediate and Insane.\n");
	printf("You will have to enter the rows and col to boom the hidden ships.\n");
	printf("To win the game you will have 40 attempts to boom 5 ships.\n");
	printf("There will be 80 hidden ships for Beginner level, 40 hidden ships for Intermediate level and 20 hidden ships for Insane level.\n");
	printf("Enter 1: Beginner level.\n");
	printf("Enter 2: Intermediate level.\n");
	printf("Enter 3: Hard level.\n");
    printf("Enter 4: Doomed level.\n");
}

void emptymap(int map[][60],int noOfships) 
{
	int rows, col;

	printf("%13d%10d%10d%10d%10d%10d\n", 1, 2, 3, 4, 5, 6);
	printf("%13d", 1234567890);
	for (col = 1; col <= 5; col++)
	{
		printf("1234567890");
	}
	printf("\n");
	for (rows = 1; rows <= 20; rows++)
	{
		printf("%2d ", rows);
		for (col = 0; col < 60; col++)
		{
			if ((map[rows - 1][col] != -1)&& (map[rows - 1][col] != -2))
			{
				printf("#");
			}
			else if (map[rows-1][col] == -1)
			{
				printf("0");
			}
			else if (map[rows-1][col] == -2)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
} 

void stage(int map[][60], int noOfships)  
{
	int x, y, ship = 1;
	srand((time)NULL);

	while (ship <= noOfships)
	{
		x = rand() % 20;
		y = rand() % 60;
		if ((map[x][y] == 0) && (map[x][y + 4] == 0) && ((y + 4) < 60))
		{
			map[x][y] = ship;
			map[x][y + 1] = ship;
			map[x][y + 2] = ship;
			map[x][y + 3] = ship;
			map[x][y + 4] = ship;
			ship++;
		}
	}
}

void bomb(int row1, int col1, int map[][60],int noOfships) 
{
	system("cls");
	int attempt = 40;
	int count = 0;
	int x, y, coordinate;
	while ((attempt > 0) && (count != 10))
	{
		attempt = attempt - 1;
		if ((map[row1 - 1][col1 - 1] >= 1) && (map[row1 - 1][col1 - 1] <= noOfships)) 
		{
			coordinate = map[row1 - 1][col1 - 1];
			for (x = 0; x <= 19; x++)
			{
				for (y = 0; y <= 59; y++)
				{
					if (map[x][y] == coordinate)
					{
						map[x][y] = -1;
					}
				}
			}
			count++;
		}
		else if ((map[row1 - 1][col1 - 1] == 0))
		{
			printf("Try again.\n");
			map[row1 - 1][col1 - 1] = -2;
		}
		printf("You have hit %d of 10 ships.\n", count);
		printf("You still have %d attempt.\n", attempt);
		emptymap(map,noOfships); 
		printf("Enter (row 'spacebar' col) to bomb:");
		scanf("%d%d", &row1, &col1);
		while ((row1 <= 0) || (row1 > 20) || (col1 <= 0) || (col1 > 60))
		{
			printf("\nEnter (row 'spacebar' col) to bomb:\n");
			scanf("%d%d", &row1, &col1);
		}
		
	}
	if (count == 5)
	{
		printf("Congratulation! You have succesfully bombed 10 ships!\n");
	}
	else
	{
		printf("Better luck next time!\n");
	}
	for (x = 0; x < 20; x++)
	{
		for (y = 0; y < 60; y++) 
		{
			map[x][y] = 0; 
		}
	}
}