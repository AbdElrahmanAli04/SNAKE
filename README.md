# Snake Game in C++ with SFML

A classic Snake game implementation using C++ and SFML graphics library. The game features a smooth-moving snake, apple collection mechanics, and an intuitive menu system.

## Features

- Smooth snake movement with collision detection
- Main menu and game over screens
- Smooth controls using arrow keys
- Wrapping boundaries (snake appears on opposite side when crossing screen edges)
- Progressive difficulty (snake grows longer with each apple)

## Prerequisites

- C++ compiler (g++ recommended)
- SFML library (2.5 or later)
- Make (optional, for building)

## Project Structure

```
SNAKE/
├── assets/
│   ├── game_over.ttf
│   ├── Playball-Regular.ttf
│   └── snake-graphics.png
├── include/
│   ├── clsFood.h
│   ├── clsGame.h
│   ├── clsGameOver.h
│   ├── clsMainMenu.h
│   ├── clsSnake.h
│   ├── clsText.h
│   └── clsUtil.h
├── src/
│   └── Main.cpp
├── .vscode/
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
└── README.md
```

## Building and Running

### Using VS Code

1. Open the project in VS Code
2. Make sure you have the C/C++ extension installed
3. Press F5 to build and run the game

### Using Terminal

```bash
# Navigate to the project directory
cd SNAKE

# Build the game
g++ -g src/Main.cpp -o snake -lsfml-graphics -lsfml-window -lsfml-system

# Run the game
./snake
```


## Controls

- ⬆️ Up Arrow: Move Up
- ⬇️ Down Arrow: Move Down
- ⬅️ Left Arrow: Move Left
- ➡️ Right Arrow: Move Right



## That's it ! Happy gaming! 🐍