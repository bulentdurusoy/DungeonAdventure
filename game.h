#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "room.h"

// Prototypes for general game functions
void start_game();
void handle_command(const char *command, Player *player, Room **current_room, int *is_game_over, Room **roomList, int roomCount);
#endif
