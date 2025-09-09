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

# Starting up the Server

1. Ensure all files are in same directory
2. Compile using gcc
'gcc -o battleship main.c helpers.c'
3. Run program to start server by inputting a port number
'./battleship <port>' (e.g. port==8710)

#Connecting to server

Open a terminal to connect to the server

'nc localhost 8080'

#Game Instructions

layers register with a name and place a single ship of length 5 on a 10×10 grid. Ships can be placed horizontally (-) or vertically (|). Players take turns bombing coordinates to try and sink each other’s ships.

#Commands

REG 








  
