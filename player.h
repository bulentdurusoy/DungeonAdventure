#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    int health;
    int strength;
    int inventory_capacity;
    char **inventory; // Dynamically allocated inventory
    int inventory_count;
} Player;

Player *create_player();
void free_player(Player *player);

#endif
