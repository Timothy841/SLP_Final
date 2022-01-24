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

Devlog: Helen and Tomas have not added their work to the devlog

Friday 7th:

Timothy, Tomas, Helen 11:29 AM : Gathered group and started brainstorming ideas.

Tuesday 11th:

Timothy, Tomas, Helen 9:38 PM : Discussed with group and finished proposal.

Monday 17th:

Timothy 9:32 PM : Added forking server and client code in. Changed forking server to only accept one client at a time. Any other clients have to wait. Just have to connect server/client to game.

Friday 21st:

Timothy : Connect server/client to games

Sunday 8:26 PM: Fixed bugs between server and client. Implemented ls and save files. Unable to implement loading.

|
|
|

Final Version:

Project Name: the Do-Nothings

Names: Timothy Sit, Tomas Acuna, Helen Zhu

Period: 5

Description: Connect 4 between two different devices

Libraries: None required

Instructions:

Use two different computers, or two terminals on the same computer. First use make to get all the code ready. Then, on one computer, type ./server and on the other, type ./client. The game will start. The client will go first, then the server. Type save and then a name for the save file to save the current game. Type ls to view all save files. I was not able to implement load, there were two many bugs to handle.

Problems:

No ability to load a game

Ending a game does not automatically end it for the opponent. ie, signals are not handled.

Final techniques used:

	Sockets to connect computers

	Files to save games

	Processes to use ls and save

	Allocating memory to create the game board and other variables
