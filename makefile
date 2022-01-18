all: server client

server: forking_server.c networking.c game.c board.c
	gcc -o server forking_server.c networking.c networking.h game.c board.c board.h

client: client.c networking.c game.c board.c
	gcc -o client client.c networking.c networking.h game.c board.c board.h

clean:
	rm *.o
