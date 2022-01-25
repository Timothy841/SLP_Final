#include "networking.h"

void error_check( int i, char *s ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    exit(1);
  }
}

void error_check_sock( int i, char *s, int sd ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    close(sd);
    exit(1);
  }
}


/*=========================
  server_setup
  args:
  creates, binds a server side socket
  and sets it to the listening state
  returns the socket descriptor
  =========================*/
int server_setup() {
  int sd, i;

  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4 address
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  hints->ai_flags = AI_PASSIVE;  //Use all valid addresses
  getaddrinfo(NULL, PORT, hints, &results); //NULL means use local address

  //create the socket
  sd = socket( results->ai_family, results->ai_socktype, results->ai_protocol );
  error_check( sd, "server socket" );
  printf("[server] socket created\n");
  //this code should get around the address in use error
  int yes = 1;
  if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ) {
    printf("sockopt  error\n");
    exit(-1);
  }

  //bind the socket to address and port
  i = bind( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "server bind" );
  printf("[server] socket bound\n");

  //set socket to listen state
  i = listen(sd, 10);
  error_check( i, "server listen" );
  printf("[server] socket in listen state\n");


  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  return sd;
}


/*=========================
  server_connect
  args: int sd
  sd should refer to a socket in the listening state
  run the accept call
  returns the socket descriptor for the new socket connected
  to the client.
  =========================*/
int server_connect(int sd) {
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;

  sock_size = sizeof(client_address);
  client_socket = accept(sd, (struct sockaddr *)&client_address, &sock_size);
  error_check(client_socket, "server accept");

  return client_socket;
}

/*=========================
  client_setup
  args: int * to_server
  to_server is a string representing the server address
  create and connect a socket to a server socket that is
  in the listening state
  returns the file descriptor for the socket
  =========================*/
int client_setup(char * server) {
  int sd, i;

  //run getaddrinfo
  /* hints->ai_flags not needed because the client
     specifies the desired address. */
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  getaddrinfo(server, PORT, hints, &results);

  //create the socket
  sd = socket( results->ai_family, results->ai_socktype, results->ai_protocol );
  error_check( sd, "client socket" );

  //connect to the server
  //connect will bind the socket for us
  i = connect( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "client connect" );

  free(hints);
  freeaddrinfo(results);

  return sd;
}

int convert_int(char board[6][7], char *buffer, int opponent_socket, char *history){//get the buffer and convert it to int. Doesn't need to check if it is valid because get_int does that
  if (!strcmp(buffer, "l")){//load
    clear_board(board);
    int player = 2;
    int h;
    read(opponent_socket, history, 200);
    for (int i = 0; i<strlen(history); i+=2){
      h = history[i]-49;
  		place_piece(board, player, h);//place piece
      if (player == 2){
        player = 1;
      }
      else{
        player = 2;
      }
    }
    print_board(board);
    return 0;
  }
  if (strlen(buffer) == 0){
    return -1;
  }
	int num = atoi(buffer);
	if (num < 1 || num > 7){
		printf("Not valid move from opponent\n");
	}
	return num;
}

int get_int(char board[6][7], char *buffer, char player, int opponent_socket, char *history) {
  if (player == 1) {
    printf("place red piece on: ");
  }
  else {
    printf("place yellow piece on: ");
  }
  fgets(buffer, sizeof buffer, stdin);
  *strchr(buffer, '\n') = 0;//if only \n in buffer, make it 0
  print_saves(board, buffer, opponent_socket, history);
  int num = atoi(buffer);
  if (strlen(buffer) != 1){//make \n not work
    num = -1;
  }
  while (num < 1 || num > 7){
    if (strcmp(buffer, "ls") && strcmp(buffer, "save") && strcmp(buffer, "load")){
      printf("Not a valid input. Try again\n");
    }
    if (player == 1) {
      printf("place red piece on: ");
    }
    else {
      printf("place yellow piece on: ");
    }
    fgets(buffer, sizeof buffer, stdin);
    *strchr(buffer, '\n') = 0;//if only \n in buffer, make it 0
    print_saves(board, buffer, opponent_socket, history);
    num = atoi(buffer);
    if (strlen(buffer) != 1){//make \n not work
      num = -1;
    }
  }
  return atoi(buffer);
}

int real_row(int r) {
  return r >= 0 && r < 6;
}

int real_col(int c) {
  return c >= 0 && c < 7;
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

void print_hole(char player) {
  if (player == 0) {
    printf("\U0001F518");//empty hole
  }
  else if (player == 1) {
    printf("\U0001F534");//player 1, server
  }
  else {
    printf("\U0001F7E1");//player 2, client
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

void print_saves(char board[6][7], char *buffer, int opponent_socket, char *history){
  if (!strcmp(buffer, "ls")){//it is ls
    int f = fork();
    if (!f){//child
      printf("\n");
      system("ls *.txt");
      printf("\n");
      close(opponent_socket);
      exit(0);
    }
    else{
      int status;
      int a = waitpid(-1, &status, 0);
    }
  }
  else if (!strcmp(buffer, "save")){//it is save
    char name[BUFFER_SIZE];
    printf("What name would you like to give your save: ");
    fgets(name, sizeof name, stdin);
    *strchr(name, '\n') = 0;
    strcat(name, ".txt");
    int fd = open(name, O_WRONLY | O_CREAT, 0644);
    write(fd, history, strlen(history));
    close(fd);
  }
  else if (!strcmp(buffer, "load")){//it is save
    memset(history, 0, 200);
    char name[BUFFER_SIZE];
    printf("Which save would you like to load: ");
    fgets(name, sizeof name, stdin);
    *strchr(name, '\n') = 0;
    strcat(name, ".txt");
    int fd = open(name, O_RDONLY);
    read(fd, history, 200);
    char *load = "l";
    write(opponent_socket, load, strlen(load));
    sleep(1);
    write(opponent_socket, history, strlen(history));
    clear_board(board);
    int player = 2;
    int h;
    for (int i = 0; i<strlen(history); i+=2){
      h = history[i]-49;
  		place_piece(board, player, h);//place piece
      if (player == 2){
        player = 1;
      }
      else{
        player = 2;
      }
    }
    print_board(board);
    close(fd);
  }
}

void clear_board(char board[6][7]) {
  for (int r = 0; real_row(r); r ++) {
    for (int c = 0; real_col(c); c ++) {
      board[r][c] = 0;
    }
  }
}

int full(char board[6][7]) {
  for (int c = 0; real_col(c); c ++) {
    if (board[0][c] == 0) {
      return -1;//board is not full, don't do anything
    }
  }
  return 0;//board is full, tie
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
  for (int r = 0; real_row(r); r ++) {
    for (int c = 0; real_col(c); c ++) {
      char winner = check_winner(board, r, c, 1, 1);
      if (winner) {
        return winner;
      }
    }
  }
  for (int r = 0; real_row(r); r ++) {
    for (int c = 0; real_col(c); c ++) {
      char winner = check_winner(board, r, c, -1, 1);
      if (winner) {
        return winner;
      }
    }
  }
  return -1;
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

void end_game(int winner, char board[6][7], int opponent_socket){
  winner = full(board);
  winner = get_winner(board);
  show_result(winner);
  if (winner != -1){
    close(opponent_socket);
    exit(0);
  }
}
