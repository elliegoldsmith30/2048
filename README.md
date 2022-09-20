# 2048

#### Ellie Goldsmith

## Overview


### Description
This code implements the commonly known game 2048. The goal of the game is to combine tiles to ultimately get the 2048 tile on the board. The game uses the following functional requirements:

1. To begin, two blocks are placed in the 4x4 grid in a random position and each tile is either a two or a four.
When an arrow key is pressed, all blocks adhere to the following rules: (x denotes no tile)
2. A block will not move if it is next to the wall and the key would move it towards that wall. (Example: A tile is next to the left wall and you press the left arrow key).
3. A block will shift over if there is an empty tile(s) next to it and stops at a tile that is of a different value than itself, the wall/end of grid, or a merge (explained later) (Ex of different value: 2 x 4 x becomes 2 4 x x when left arrow is pressed) and (Ex of wall: x 2 x x becomes 2 x x x when left key is pressed).
4.  If two tiles are the same number and the arrow keys are pressed that would shift in the proper direction, it becomes one new tile with the value being 2 times the amount of any one of the tiles/the addition of the two numbers. ( 2 x 2 x becomes 4 x x x when the left arrow key is pressed).
General Rules:
5. Multiple merges can occur at the same time in different rows/columns if each row/column would result in a merge by pressing a single arrow key.
6. Multiple merges can occur at the same time in one row/column if there are four tiles in that row/column and the two sets of the same number are next to each other. (Ex: 2 2 4 4 becomes 4 8 x x when the left arrow key is pressed).
7. Any time an arrow key is pressed, another 2 or a 4 appears in a random position on the board unless pressing that arrow key would result in no changes on the board. (Ex: if you press the right arrow key, nothing will change because everything is already as far right as possible, so no new tile will be added to the screen).
8. The score increases every time two tiles combine and the value added to the score is the new tile created (addition of two tiles being combined).
9.  The game is over/you die when there are no more possible combinations that can be made and all spaces on the board are full and you press an arrow key.
10. When the 2048 tile appears on the screen, the player wins but can click anywhere on the screen to continue playing.
11. The score is displayed in the top right corner of the screen and displayed in the middle of the screen when a player dies.
12. When the player wins by getting to 2048, a box appears in the middle of the screen with a winner message and instructions for how to continue.



## Install

In order to install this game, you must download CLion. Open the application with the board.cxx file. At the dropdown menu towards the right of the top bar, set it to debug and press run. Use the arrow keys to play to the game. 


## Credits
Code outlined by Northwestern Professor Sruti Bhagavatula.
