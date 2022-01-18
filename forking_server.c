#include "networking.h"
#include "board.h"
void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();
  int client_socket = server_connect(listen_socket);
  subserver(client_socket);
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];
  char board[6][7];//create board
  clear_board(board);//clear it
  print_board(board);//print clean board
  while (read(client_socket, buffer, sizeof(buffer))) {//receive input
	print_board(board);//print input on board;
    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);//do server input
    write(client_socket, buffer, sizeof(buffer));//give input to client
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
	while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
