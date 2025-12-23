# Merge Grid Engine

Merge Grid Engine is a console-based grid merging game written in C++.  
It is inspired by the 2048 puzzle and focuses on logic building, state management and clean implementation rather than graphics.

## Features
- Grid based tile merging game
- Configurable grid size (4x4 or 5x5)
- Custom merge rule for equal tiles
- Undo support for the last move
- Score tracking and game-over detection

## Controls
W - Move Up  
A - Move Left  
S - Move Down  
D - Move Right  
U - Undo last move  
Q - Quit the game  

## How it works
Each move follows three steps:
- Shift tiles in the selected direction
- Merge adjacent equal tiles
- Shift again to remove gaps after merging  

A new tile (2 or 4) appears after every valid move.
