#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "room.h"

Room *create_room(char *description)
{
    Room *room = (Room *)malloc(sizeof(Room));
    if (!room)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    room->description = strdup(description);
    for (int i = 0; i < 4; i++)
    {
        room->connections[i] = NULL;
    }
    for (int i = 0; i < 100; i++)
    {
        room->items[i] = NULL; // Initialize item slots to NULL
    }
    room->item_count = 0;
    room->creature = NULL;
    return room;
}

void connect_rooms(Room *room1, int direction, Room *room2)
{
    if (direction >= 0 && direction < 4)
    {
        room1->connections[direction] = room2;

        if (direction == 0 || direction == 2)
        {
            room2->connections[(direction + 1)] = room1;
        }
        else if (direction == 1 || direction == 3)
        {
            room2->connections[(direction - 1)] = room1;
        }
    }
}

void add_item_to_room(Room *room, char *item)
{
    if (room->item_count >= 100)
    {
        printf("Room cannot hold more items!\n");
        return;
    }
    room->items[room->item_count] = strdup(item); // Create a copy and add it to the room
    room->item_count++;
}

void add_creature_to_room(Room *room, Creature *creature)
{
    room->creature = creature;
}
