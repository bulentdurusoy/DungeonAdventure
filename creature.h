#ifndef CREATURE_H
#define CREATURE_H

typedef struct
{
    char *name;
    int health;
    int strength;
} Creature;

Creature *create_creature(const char *name, int health, int strength);
void free_creature(Creature *creature);

#endif
