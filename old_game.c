#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int get_int(char player) {
  char input[100];
  fgets(input, sizeof input, stdin);
  int num = atoi(input);
  while (num < 1 || num > 7){
    printf("Not a valid input. Try again\n");
    if (player == 1) {
      printf("place red piece on: ");
    }
    else {
      printf("place yellow piece on: ");
    }
    fgets(input, sizeof input, stdin);
    num = atoi(input);
  }
  return atoi(input);
}

int do_turn_attempt(char board[6][7], char player) {
  if (player == 1) {
    printf("place red piece on: ");
  }
  else {
    printf("place blue piece on: ");
  }
  int c = get_int(player);
  int fail = place_piece(board, player, c - 1);
  if (fail) {
    printf("slot %c is full\n", c);
  }
  return fail;
}

void do_turn(char board[6][7], char player) {
  while (do_turn_attempt(board, player)) {}
}

void show_result(char winner) {
  if (winner == 0) {
    printf("The game is a tie!\n");
  }
  else if (winner == 1) {
    printf("Red wins!\n");
  }
  else if (winner == 2) {
    printf("Yellow wins!\n");
  }
}

void play_game() {
  char board[6][7];
  clear_board(board);
  char player = 1;
  char winner = 0;
  while (!full(board) && !winner) {
    print_board(board);
    do_turn(board, player);
    winner = get_winner(board);
    if (player == 1) {
      player = 2;
    }
    else {
      player = 1;
    }
  }
  show_result(winner);
}

int main() {
  play_game();
  return 0;
}
