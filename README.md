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

  # Server start up

  
