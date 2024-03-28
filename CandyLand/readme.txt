------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -std=c++17 -Wall -Werror -Wpedantic Player.cpp  Board.cpp  CandyStore.cpp  Game.cpp gamedriver.cpp

Run: .\a.exe 
------------------------
DEPENDENCIES
------------------------
Player.h, Board.h, Game.h, candies.txt, riddles.txt and characters.txt must be in the same directory as the cpp files to compile.
------------------------
Author: Abdullahi Husein 
------------------------
ABOUT THIS PROJECT
------------------------
This project implements an interactive board game fashioned after the game
Candy Land. Two players draw random cards to move on the board. They are met 
with hidden treasures, special tiles, and pop-up stores in random positions. 
They can use the candy to buff, de-buff, or even impede their opponents from moving. 
The goal is to get to the Castle, the end of the Candy Land trail, to win the game. 

