#include "networking.h"

void subserver(int from_opponent);

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();
  int opponent_socket = server_connect(listen_socket);
  subserver(opponent_socket);
}

void subserver(int opponent_socket) {
  char buffer[BUFFER_SIZE];
  char *history = calloc(200,1);
  int player = 2;
  int winner = -1;
  char board[6][7];//create board
  clear_board(board);//clear it
  printf("Type in {0, 1, 2, 3, 4, 5, 6} to put your piece on the board. Type in {ls} to see all save files. Type {save} to save. Type {load} to load a save. Don't {load} twice in the same game.\n");
  print_board(board);//print clean board
  while (1){
  	if (player == 1){
  		int move = get_int(board, buffer, player, opponent_socket, history);//get input to write
  		int fail = place_piece(board, player, move-1);//see if move fails
  		if (fail){
  			continue;//start over, new move
  		}
  		print_board(board);
    	write(opponent_socket, buffer, sizeof(buffer));//give input to opponent
      strcat(history, strcat(buffer, ","));
      end_game(winner, board, opponent_socket);
      player = 2;
  	}
  	else{
      read(opponent_socket, buffer, sizeof(buffer));//read opponent move
      int move = convert_int(board, buffer, opponent_socket, history);//convert to int
      if (move == -1){
        printf("Game ended\n");
        exit(0);
      }
      else if (move == 0){
        continue;
      }
      strcat(history, strcat(buffer, ","));
      place_piece(board, player, move-1);//place piece
      print_board(board);
      end_game(winner, board, opponent_socket);
      player = 1;
  	}
  }
  close(opponent_socket);
  exit(0);
}
