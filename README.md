NMM
===

NineMensMorris, online

GameLib is a DLL containing the core game, the map the two players 
turns rules ect.

Client is a DLL that handles everything the client has to do, except 
rendering a GUI. It connect to the server, communicate with the server
sync the local game with the server ect.
In the future also handles single player and local co-op

Server handles the server side of the online part, keeps track of the 
game state, communicate and update the clients gets the connections
ect.

ClientTest is simple GUI to test the client part of the program, the
reason this is not a part of the client, is that other rendering 
options should still be open, and its easier with a total seperation
of client logic and render logic