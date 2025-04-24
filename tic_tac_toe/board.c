#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void set_board(char board[3][3]) //we set every element from board with ' ' 
{
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      board[i][j] = ' ';
}

void display_board(char board[3][3]) //we display the board with the current moves made by the players
{
  for(int i = 0; i < 3; i++)
    {
      if(i == 1)
	{
	  printf("-----------\n");
	}
      printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
      if(i == 1)
	{
	  printf("-----------\n");
	}
    }
}

void clearScreen() //clears the terminal
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
