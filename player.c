#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

Player *create_player()
{
    Player *player = (Player *)malloc(sizeof(Player));
    if (!player)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(1);
    }

    player->health = 100;
    player->strength = 10;
    player->inventory_capacity = 1;
    player->inventory = (char **)malloc(player->inventory_capacity * sizeof(char *));
    player->inventory_count = 0;

    return player;
}

void free_player(Player *player)
{
    if (player)
    {
        for (int i = 0; i < player->inventory_count; i++)
        {
            free(player->inventory[i]);
        }
        free(player->inventory);
        free(player);
    }
}
