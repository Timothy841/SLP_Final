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

int check_hole(char board[6][7], char *last, int *consec, int r, int c) {
  if (board[r][c] == *last) {
    (*consec) ++;
    if (*consec >= 4) {
      return 1;
    }
  }
  else {
    *last = board[r][c];
    *consec = 1;
  }
  return 0;
}

char get_winner(char board[6][7]) {
  char last;
  int consec;
  for (int r = 0; real_row(r); r ++) {
    last = 0;
    consec = 0;
    for (int c = 0; real_col(c); c ++) {
      if (check_hole(board, &last, &consec, r, c)) {
        return last;
      }
    }
  }
  for (int c = 0; real_col(c); c ++) {
    last = 0;
    consec = 0;
    for (int r = 0; real_row(r); r ++) {
      if (check_hole(board, &last, &consec, r, c)) {
        return last;
      }
    }
  }
  return 0;
}
