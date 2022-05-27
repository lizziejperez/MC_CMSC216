# Project: Dungeon Crawl
## Overview
Implement a "simple" dungeon simulation in C.
### Objectives
- Process data from Standard Input (STDIN)
- Allocate and manage memory dynamically
- Build and traverse arbitrarily complex data-structures in memory
## Description
### Introduction
In the early days of the computer revolution, many games featured the player exploring an underground dungeon.
### What to do
Create a C program called "dungeon" that implements a Dungeon Crawler game. Your program should take three sets of input: a map/item specification, a starting location for the player and the dragon, and then the player's sequence of moves.
### Game Details
- Infinite rooms
- Infinite connections between rooms
- Max 1 item/room
- Player may have max of 1 item
- Player dies if in the room with the dragon without a sword
- Dragon dies if in the room iwht the player with a sword
- Maps need not be connected or complete
- Some connection are one-way
- Must use dynamic memory allocation for the main data structure
### Gameplay
During the game the player will explore a potentially infinite number of rooms connected by a potentially infinite number of hallways searching for the dragon.
While exploring the map your program should give the player feedback about whether he is getting closer to the dragon "warmer" or further from what does "colder".
Your program should also provide varying levels of descriptive detail regarding the adjoining rooms and some indication of the distance to the dragon.
In each room the player may either choose to move to an adjacent room (by entering its room id), or pick up the item in the current room (by entering zero).
If the player picks up an item while holding an existing item, the existing item will be dropped and replaced by the new item.
Attempting to pick-up an item in an empty room will drop any item your are holding.
If at any time the player is in the same room as the dragon without also being in possession of a sword, the player will be eaten, lose the game, and your program should exit.
If during the course of play the user should find himself in the room with the dragon and is currently in possession of the sword, he uses it to kill the dragon, the player will win the game and your program should exit.
### Input Specification
- Map
   * Consists of a potentially infinite number of lines each including a room identifier (given as an long long integer) and then a comma delimited list of adjoining rooms (given as a set of comma-separated, long long integers enclosed in parentheses), followed by a potential item in the room. Items will be string values with a length up 255 characters, and may not include the newline character. To end the input of rooms, the user should enter (invalid) room zero.
- Starting Locations
   * Consists of a comma separated pair of long long integers indicating the starting location of the player and the dragon in that order.
- Player Moves
   * Are indicated as a series of long long integers separated by newlines (\n). When the player would like to pick up an item (or switch items), he should enter room zero.
## Compiling
```
gcc -Wall -pedantic-errors -Werror -c dungeon.c
```
