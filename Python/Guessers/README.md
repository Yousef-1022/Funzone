# Guessers
- Simple TCP Client-Server application where multiple clients have to guess the correct number the server has chosen

## Way the program works:
- Run the server, and then simply run multiple clients
- The clients keep guessing the number, if one client gets it right, the other clients lose and the server makes them disconnect, and then restarts the game.
- If a client guessed incorrectly, only the client leaves the game while the others keep playing.