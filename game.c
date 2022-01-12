#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int get_int() {
  char input[100];
  fgets(input, sizeof input, stdin);
  return atoi(input);
}

int do_turn_attempt(char board[6][7], char player) {
  if (player == 1) {
    printf("place red piece on: ");
  }
  else if (player == 2) {
    printf("place blue piece on: ");
  }
  int c = get_int();
  int fail = place_piece(board, player, c - 1);
  if (fail) {
    printf("slot %c is full\n", c);
  }
  return fail;
}

void do_turn(char board[6][7], char player) {
  while (do_turn_attempt(board, player)) {}
}

void play_game() {
  char board[6][7];
  clear_board(board);
  char player = 1;
  while (!full(board)) {
    print_board(board);
    do_turn(board, player);
    if (player == 1) {
      player = 2;
    }
    else if (player == 2) {
      player = 1;
    }
  }
}

int main() {
  play_game();
  return 0;
}
