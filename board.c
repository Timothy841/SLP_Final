#include <stdio.h>

void clear_board(char board[6][7]) {
  for (int r = 0; r < 6; r ++) {
    for (int c = 0; c < 7; c ++) {
      board[r][c] = 0;
    }
  }
}

int place_piece(char board[6][7], char player, int c) {
  for (int r = 5; r >= 0; r --) {
    if (board[r][c] == 0) {
      board[r][c] = player;
      return 0;
    }
  }
  return 1;
}

int full(char board[6][7]) {
  for (int c = 0; c < 7; c ++) {
    if (board[0][c] == 0) {
      return 0;
    }
  }
  return 1;
}

void print_hole(char player) {
  if (player == 0) {
    printf("\U0001F518");
  }
  else if (player == 1) {
    printf("\U0001F534");
  }
  else if (player == 2) {
    printf("\U0001F535");
  }
}

void print_board(char board[6][7]) {
  printf("1 2 3 4 5 6 7 \n");
  for (int r = 0; r < 6; r ++) {
    for (int c = 0; c < 7; c ++) {
      print_hole(board[r][c]);
    }
    printf("\n");
  }
}
