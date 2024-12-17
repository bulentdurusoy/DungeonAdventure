#ifndef ROOM_H
#define ROOM_H

#include "creature.h"

typedef struct Room
{
    char *description;
    struct Room *connections[4]; // 0: up, 1: down, 2: left, 3: right
    char *items[100];
    ;
    int item_count;
    Creature *creature; // Creature in the room
} Room;

Room *create_room(char *description);
void connect_rooms(Room *room1, int direction, Room *room2);
void add_item_to_room(Room *room, char *item);
void add_creature_to_room(Room *room, Creature *creature);
void free_room(Room *room);

#endif
