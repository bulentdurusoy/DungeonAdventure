# Dungeon Adventure Game

## Description
**Dungeon Adventure** is a text-based, command-line adventure game implemented in C. Players navigate through a dungeon, collect items, fight creatures, and aim to find the key to unlock the final room and win the game. The project demonstrates key programming concepts like dynamic memory allocation, file I/O, modular design, and a robust save/load system using JSON.

---

## Features
- **Room Navigation**: Move between interconnected rooms with up, down, left, and right commands.
- **Inventory Management**: Collect and drop items with limited inventory capacity.
- **Combat System**: Turn-based combat with creatures where stats like health and strength determine the outcome.
- **Save/Load Game**: Save your progress into a JSON file and reload it later.
- **Randomized Elements**: Rooms, creatures, and items are added dynamically during gameplay.
- **Error Handling**: Invalid commands, memory issues, and file errors are handled robustly.

---

## Gameplay Instructions

### Available Commands
- `move <direction>`: Move in a specified direction (up, down, left, right).
- `look`: View the room description, items, and creatures.
- `inventory`: Display items in your inventory.
- `pickup <item>`: Pick up an item in the room.
- `drop <item>`: Drop an item from your inventory.
- `attack`: Attack a creature in the room.
- `save`: Save the current game state to a JSON file.
- `load <filename>`: Load a previously saved game state.
- `list`: List all saved game files in the current directory.
- `exit`: Exit the game.

### Objective
Your mission is to navigate through the dungeon, defeat creatures, collect key items, and unlock the final room to escape successfully.

---

## Project Structure
DungeonAdventure
main.c           # Entry point of the game
game.c/.h        # Core game logic (commands, combat, save/load)
player.c/.h      # Player attributes and inventory management
oom.c/.h         # Room connections, items, and creatures
creature.c/.h    # Creature structure and combat stats
cJSON/           # cJSON library for JSON parsing
CMakeLists.txt   # Build configuration file for CMake
README.md        # Project documentation

Dependencies
•	cJSON: A lightweight JSON parsing library used for save/load functionality.
o	Install cJSON on Linux:
sudo apt-get install libcjson-dev







Build and Run Instructions
Prerequisites
•	GCC Compiler
•	cJSON library (for JSON-based save/load functionality)
•	CMake (optional, for automated build, minimum version 3.10)
Compilation Instructions
Run the following commands in the terminal:
mkdir build
cd build
cmake ..
make

To run the game:
./DungeonAdventure


Manuel Compile
1.Compile All Source Files Together:
Use the following gcc command to compile all .c files into a single executable:
gcc -o DungeonAdventure main.c game.c player.c room.c creature.c ./cJSON/cJSON.c
2.Run the game:
./DungeonAdventure



Best Regards;
Bülent Durusoy



