#include "networking.h"

int main(int argc, char **argv) {

  int opponent_socket;
  char buffer[BUFFER_SIZE];
  char *history = calloc(200,1);

  if (argc == 2)
    opponent_socket = client_setup( argv[1]);
  else
    opponent_socket = client_setup( TEST_IP );

  int player = 2;
  int winner = -1;
  char board[6][7];//create board
  clear_board(board);//clear it
  printf("Type in {0, 1, 2, 3, 4, 5, 6} to put your piece on the board. Type in {ls} to see all save files. Type {save} to save. Type {load} to load a file.\n");
  print_board(board);//print clean board
  while (1) {
  	if (player == 1){
  		read(opponent_socket, buffer, sizeof(buffer));//read opponent move
  		int move = convert_int(board, buffer, opponent_socket, history);//convert to int
      if (move == 0){
        continue;
      }
      strcat(history, strcat(buffer, "\n"));
  		place_piece(board, player, move-1);//place piece
  		print_board(board);
      end_game(winner, board, opponent_socket);
      player = 2;
  	}
  	else{
  		int move = get_int(board, buffer, player, opponent_socket, history);//get input to write
  		int fail = place_piece(board, player, move-1);//see if move fails
  		if (fail){
  			continue;//start over, new move
  		}
  		print_board(board);
    	write(opponent_socket, buffer, sizeof(buffer));//give input to opponent
      strcat(history, strcat(buffer, "\n"));
      end_game(winner, board, opponent_socket);
      player = 1;
  	}
  }
}
