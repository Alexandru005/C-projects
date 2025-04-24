#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"

int main()
{
  char board[3][3];
  int player = 1; //with this contor we decides who's turn is
  int verify;
  int result;
  
  clearScreen(); //clear terminal for the game
  set_board(board); //set all elements null
  display_board(board);

  do
    {
      if(player % 2 == 1) //your turn
	{
	  printf("\n");
	  printf("Player turn\n");
	  
	  int step = 0;
	  do //choose where to put X
	    {
	      if(step != 0)
		{
		  printf("Choose again!\n");
		}
	  
	      verify = player_turn(board); //save the result from the function

	      step++; //remember how many times we read positions
	  
	    }while(verify == 1); //if the result is 1 it means we need to read again

	  player = player + 1;
	}

      else //bot turn
	{
	  printf("\n");
	  printf("Bot turn\n");
	  printf("\n");
	  
	  do //choose where to put 0
	    {
	      
	     verify = robot_turn(board);
	      
	    }while(verify == 1);
     
	  player = player - 1;
	}
      
      clearScreen(); //clear the terminal for the new board
      display_board(board); //display new board
      printf("\n");

      result = verify_winner(board); //remember the result in case we exit the loop
       
    }while(result == 0);


  //display who wins
  if(result == 1)
    printf("Player wins\n");
  
  if(result == 2)
    printf("Draw\n");
  
  if(result == -1)
    printf("Bot wins\n");
  
  return 0;
}
