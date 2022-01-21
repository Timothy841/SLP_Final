#include <stdio.h>

int real_row(int r) {
  return r >= 0 && r < 6;
}

int real_col(int c) {
  return c >= 0 && c < 7;
}


void clear_board(char board[6][7]) {
  for (int r = 0; real_row(r); r ++) {
    for (int c = 0; real_col(c); c ++) {
      board[r][c] = 0;
    }
  }
}

int place_piece(char board[6][7], char player, int c) {
  for (int r = 5; real_row(r); r --) {
    if (board[r][c] == 0) {
      board[r][c] = player;
      return 0;
    }
  }
  return 1;
}

int full(char board[6][7]) {
  for (int c = 0; real_col(c); c ++) {
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
  else {
    printf("\U0001F535");
  }
}

void print_board(char board[6][7]) {
  printf("1 2 3 4 5 6 7 \n");
  for (int r = 0; real_row(r); r ++) {
    for (int c = 0; real_col(c); c ++) {
      print_hole(board[r][c]);
    }
    printf("\n");
  }
}

char check_winner(char board[6][7], int r, int c, int dr, int dc) {
  char last;
  char consec;
  while (real_row(r) && real_col(c)) {
    if(last && last == board[r][c]) {
      consec ++;
      if (consec >= 4) {
        return last;
      }
    }
    else {
      last = board[r][c];
      consec = 1;
    }
    r += dr;
    c += dc;
  }
  return 0;
}


char get_winner(char board[6][7]) {
  for (int r = 0; real_row(r); r ++) {
    char winner = check_winner(board, r, 0, 0, 1);
    if (winner) {
      return winner;
    }
  }
  for (int c = 0; real_col(c); c ++) {
    char winner = check_winner(board, 0, c, 1, 0);
    if (winner) {
      return winner;
    }
  }
  return 0;
}
