#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "game.h"

int player_turn(char board[3][3])
{
  //choose option
  int option;
  printf("Option:");
  scanf("%d", &option);
  printf("\n");

  int step = 0, found = 0;
  //search the position where we want to put X
  //if we find that position empty we turn found in 1
  //if we find that position and it is not empty we return 1
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      {
	step++;
	if(step == option)
	  if(board[i][j] == ' ')
	    {
	      board[i][j] = 'X';
	      found = 1;
	    }
	  else
	    return 1;
      }
  
  if(found == 0) //verify if we succed to put X where we want
    return 1;

  return 0;
}

int robot_turn(char board[3][3])
{
  srand(time(NULL));
  int option = rand() % 10; //choose the position with random for the robot

  //in rest it goes same as player_turn()

  int step = 0, found = 0;
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      {
	step++;
	if(step == option)
	  if(board[i][j] == ' ')
	    {
	      board[i][j] = '0';
	      found = 1;
	    }
	  else
	    return 1;
      }
  
  if(found == 0)
    return 1;
  
  return 0;
}

int verify_winner(char board[3][3])
{
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == 'X')
                return 1;
            else
                return -1;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != ' ' &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]) {
            if (board[0][j] == 'X')
                return 1;
            else
                return -1;
        }
    }

    // Check main diagonal
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'X')
            return 1;
        else
            return -1;
    }

    // Check anti-diagonal
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'X')
            return 1;
        else
            return -1;
    }

    // Check for empty spaces (game is not finished)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;

    // If no winner and no empty spaces, it's a draw
    return 2;
}


