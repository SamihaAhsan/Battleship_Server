# Battleship_Server 🎯

This project is a multiplayer Battleship server written in C.
It uses sockets and epoll for handling multiple clients at once, allowing players to register ships, send bomb commands, and receive real-time updates about the game state.

# 🛠️ Features

- Multiplayer support with non-blocking I/O using epoll.

- Registration system for joining with a name and placing a ship on the board.

- Bombing system for attacking coordinates on the grid.

- Validation checks for invalid names, duplicate registrations, and invalid moves.(Edge cases)

- Broadcasting system to notify all players of important events.

- Management for when players disconnect or lose.


# 🧰 Requirements

- GCC

- Linux/Unix environment

# Starting up the Server ⭐

1. Ensure all files are in same directory
2. Compile using gcc
`gcc -o battleship main.c helpers.c`

4. Run program to start server by inputting a port number
`./battleship <port>' (e.g. port==8710)`

#Connecting to server

Open a terminal to connect to the server

`nc localhost 8080`

# Game Instructions 🎮

Board: Played on a 10×10 grid with coordinates from (0,0) to (9,9).

Ships: Each player has a single ship, either horizontal (1×5) or vertical (5×1).

Joining: Players can connect anytime by registering with a name and ship placement.

Bombing: Any player can bomb any cell at any time.

If a bomb hits one or more ships, the server announces the hit or else announces a miss.

Damage: Each ship has 5 cells. Once all are damaged, that ship is sunk, and the player loses and is automatically disconnected.

Leaving: Disconnecting is treated the same as losing.

Broadcasts: The server announces all major events:

New players joining

Bombing results

Player elimination 

# Commands used ⚙️

`REG` <name> <x> <y> <d> 

where <name> is up to 20 characters

(x, y): ship center coordinates

<d>: - for horizontal (1×5), | for vertical (5×1)

Server sends to Client:

`INVALID` → bad syntax or invalid placement

`TAKEN` → name already in use

`WELCOME` → registration successful

Broadcast: JOIN <name>

Bombing
Client → Server:

`BOMB` <x> <y>

Server Broadcasts:

`HIT` <attacker> <x> <y> <victim> → if one or more ships are hit

`MISS` <attacker> <x> <y> → if no ship is hit

Game End / Disconnect
Broadcast:

`GG` <name>
→ Sent when a player’s ship is destroyed or they disconnect.








  
