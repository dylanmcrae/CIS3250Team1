********************************
CIS 3250 Team 1   Assignment 3
October 2017      Boggle Game
********************************

********************************
Program Description
********************************
Boggle Program:

When run, plays a single player game of Boggle in which your are attempting to find the most amount of words possible.

Program Functionality: 
when program is run displays a grid of letters on the console and player begins to play game. The game consists of the player looking for words within the grid. when words are entered, words are compared to words listed in englishWords text file. If the text file contains the user entered word and the word has not previously been entered, than the score is adjusted and incremented by one. Once no more words can be found or player wants to restart player enters n, or q to quit.  

functionality keywords:
q - quit
n - resets the game (new game) -> asks you for name and saves your score to leaderboard under a username

********************************
Compilation
********************************
using created makefile 
type make
and enter ./program

