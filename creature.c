#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "creature.h"

Creature *create_creature(const char *name, int health, int strength)
{
    Creature *creature = (Creature *)malloc(sizeof(Creature));
    if (!creature)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(1);
    }

    creature->name = strdup(name);
    creature->health = health;
    creature->strength = strength;

    return creature;
}

void free_creature(Creature *creature)
{
    if (creature)
    {
        free(creature->name);
        free(creature);
    }
}
