# SLP_Final

Proposal:

Project Name: the Do-Nothings

Names: Timothy Sit, Tomas Acuna, Helen Zhu

Period: 5

Statement: Connecting players on two separate devices to play Connect 4.

Description: From the terminal, a player can connect to another computer and start the game. A standard Connect 4 game board will open up on both computers.

Technical Description:

	Sockets to connect computers

	Files to save games

	Semaphores to make sure the players take turns

	Allocating memory to create the game board.

	The board will be a calloc() 2d array and the players will send a structure of two ints to each other representing the x,y coordinate. Every time you take a turn, you down the semaphore so you can't move. The other player takes their turn and ups your semaphore so you can make your move.

Timeline: I don't know the specifics.

We'll make sure that we can program the game in the first place, then we'll connect it to another computer. Making a save file will be the last one to program.

Devlog:

Friday 7th:

Timothy, Tomas, Helen 11:29 AM : Gathered group and started brainstorming ideas.

Tuesday 11th:

Timothy, Tomas, Helen 9:38 PM : Discussed with group and finished proposal.

Monday 17th:

Timothy 9:32 PM : Added forking server and client code in. Changed forking server to only accept one client at a time. Any other clients have to wait. Just have to connect server/client to game.
