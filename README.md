# Shogi
# Compile
Use the following command to compile all the file
```bash
gcc chess_board.h chess_board.c coord.c coord.h     file_processing.h file_processing.c main.c stack.c stack.h step.h
```
# Usage
## Start new game
1. Pass the following argument to start a new game:
```bash
–n –s file_name
```
* -n: start new game
* -s file_name: game record will be saved as "file_name.bin"
2. When the game starts, the input should meet the following format
* 's' for saving the game
* 'q' for quitting the game
* '0' for taking a move back
* Input the coordinate of the chess pice you want to move and input the destination of that chess pice
The following example move the chess pice from "row 8, col 3" to "row 8,col 4":
```
83 84
```
The program will check if the move if valid, if not the program will output "invalid input !"
The player then have to enter their action again

If the chess pice can be promoted after the move the player can choose to promote or not
* Enter '0' to remain the same 
* Enter '1' to promote

The game will end when one of the king is captured

## Load old game
1. Pass the following argument to load a game:
```bash
–l file_name
```
* -l file_name: load the game record "file_name.bin"
2. After the game is loaded the user can choose action by the following inputs:
* 'f' for moving to next step
* 'b' for moving to previous step
* 'q' for quitting 

目前剩下計時功能
(希望助教能給我多一點時間完成，預計11/1晚上12:00前完成)  

