#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "creature.h"
#include <time.h>
#include "./cJSON/cJSON.h"
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Define a linked list node structure for tracking added rooms
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Create a new node for the linked list
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Append a new node to the linked list
void append(Node **head, int data)
{
    Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Search for a specific number in the linked list
int findNumber(Node *head, int number)
{
    while (head != NULL)
    {
        if (head->data == number)
        {
            return 1; // Number founded
        }
        head = head->next;
    }
    return 0; // Number not found
}

// Generate a random number between min and max
int generateRandomNumber(int max, int min)
{
    return (rand() % (10 - 1 + 1)) + 1;
}

// Add a random item to a random room
void addRandomItemToRooms(Room *roomList, int roomListLength, char *itemName)
{
    int randomIndexNumber = generateRandomNumber(10, 1);
    add_item_to_room(&roomList[randomIndexNumber], itemName);
}

// Assign a creature to a room's creature pointer
void assign(Creature **creature, Creature *creature2)
{
    *creature = creature2;
}

// Add random creatures to rooms, ensuring each creature is added to a unique room
void addRandomCreaturesToRooms(Room *roomList, int roomListLength)
{
    int numberOfCreature = 6;
    Creature *creatureList = (Creature *)malloc(numberOfCreature * sizeof(Creature));
    creatureList[0] = *create_creature("Goblin", 50, 10);
    creatureList[1] = *create_creature("Ork", 30, 5);
    creatureList[2] = *create_creature("Dragon", 70, 30); // Dragon guards the key
    creatureList[3] = *create_creature("Oplimtus", 50, 8);
    creatureList[4] = *create_creature("Gubus", 40, 8);
    creatureList[5] = *create_creature("Akbas", 80, 12);

    Node *addedList = NULL;
    for (int i = 0; i < numberOfCreature; i++)
    {
        int randomIndexNumber = generateRandomNumber(roomListLength, 1);

        // Ensure no duplicate room assignment
        while (findNumber(addedList, randomIndexNumber))
        {
            randomIndexNumber = generateRandomNumber(roomListLength, 1);
        }
        append(&addedList, randomIndexNumber);

        // Assign creature to the room
        assign(&(roomList[randomIndexNumber].creature), &creatureList[i]);

        // If the creature is a Dragon, place the Key in the room
        if (strcmp(creatureList[i].name, "Dragon") == 0)
        {
            add_item_to_room(&roomList[randomIndexNumber], "key");
        }
    }
}

// List all saved games (files with .json extension) in the current directory
void list_saved_games()
{
    struct dirent *entry;
    int jsonFileFound = 0;

    // Open the current directory
    DIR *currentDir = opendir(".");
    if (!currentDir)
    {
        perror("Failed to open the current directory");
        return;
    }

    printf("Saved games:\n");

    // Iterate through files in the directory
    while ((entry = readdir(currentDir)) != NULL)
    {
        // Check if the file ends with ".json"
        if (strstr(entry->d_name, ".json") &&
            strcmp(entry->d_name + strlen(entry->d_name) - 5, ".json") == 0)
        {
            printf("- %s\n", entry->d_name);
            jsonFileFound = 1;
        }
    }

    // If no .json files are found, print a message
    if (!jsonFileFound)
    {
        printf("No saved games found\n");
    }

    // Close the directory
    closedir(currentDir);
}

// Start a new game and initialize the dungeon map
void start_game()
{
    // Seed random number generator
    srand(time(NULL));

    // Create player and starting room
    Room *roomList = (Room *)malloc(11 * sizeof(Room));
    int roomListLength = 11;
    Player *player = create_player();

    // Initialize rooms
    roomList[0] = *create_room("1 This is a dark starting room. You see a door above.");
    roomList[1] = *create_room("2 This is a narrow room. There is a door to the right and another door to the up.");
    roomList[2] = *create_room("3 This is a vast and airy room. There are  doors on the right, left, up and down.");
    roomList[3] = *create_room("4 This is a moldy room. There is a door to the left and another door to the up.");
    roomList[4] = *create_room("5 This is a soggy room.. There is a door to the down and another door to the up.");
    roomList[5] = *create_room("6 This is a humid room. There is a door to the down, another door to the up and another door to the right.");
    roomList[6] = *create_room("7 This is a filthy room. There is a door to the down, another door to the up and another door to the left.");
    roomList[7] = *create_room("8 This is a suffocating room.. There is a door to the down and another door to the right.");
    roomList[8] = *create_room("9 This is a dusty room.. There are  doors on the right, left, up and down.");
    roomList[9] = *create_room("10 This is a shadowy room. There is a door to the down and another door to the left.");
    roomList[10] = *create_room("11 This is a sunlit room. This is last room");

    // 0 -> "up"
    // 1 -> "down"
    // 2 -> "left"
    // 3 -> "right"

    // Add connections between rooms
    connect_rooms(&roomList[0], UP, &roomList[2]);
    connect_rooms(&roomList[2], RIGHT, &roomList[3]);
    connect_rooms(&roomList[2], LEFT, &roomList[1]);

    connect_rooms(&roomList[2], UP, &roomList[5]);
    connect_rooms(&roomList[1], UP, &roomList[4]);
    connect_rooms(&roomList[3], UP, &roomList[6]);
    connect_rooms(&roomList[5], RIGHT, &roomList[6]);

    connect_rooms(&roomList[4], UP, &roomList[7]);
    connect_rooms(&roomList[5], UP, &roomList[8]);
    connect_rooms(&roomList[6], UP, &roomList[9]);
    connect_rooms(&roomList[7], RIGHT, &roomList[8]);
    connect_rooms(&roomList[8], RIGHT, &roomList[9]);

    connect_rooms(&roomList[8], UP, &roomList[10]);

    // Add random items
    addRandomItemToRooms(roomList, roomListLength, "sword");
    addRandomItemToRooms(roomList, roomListLength, "shield");
    addRandomItemToRooms(roomList, roomListLength, "armor");

    // Add random creatures
    addRandomCreaturesToRooms(roomList, roomListLength);

    // Start in the first room
    Room *current_room = &roomList[0];

    int is_game_over = 0;

    printf("Welcome to Dungeon Adventure!\n");
    printf("\nYou must find the key to exit the exit door.!\n");
    printf("A challenging journey awaits you. Good luck!\n");

    printf("\nCommands: move <direction>, look, inventory, pickup <item>, drop <item>, list, attack, save, load <file>, exit\n");


    // Main game loop
    char command[256];
    while (!is_game_over)
    {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting the game...\n");
            break;
        }
        handle_command(command, player, &current_room, &is_game_over, &roomList, roomListLength);
    }

    free_player(player);
    free(roomList);
}

int file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// Save the game state to a file
void save_game(Room *rooms, int room_count, Player *player, int currentRoomNumber)
{
    cJSON *root = cJSON_CreateObject();

    // Save player data
    cJSON *json_player = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_player, "health", player->health);
    cJSON_AddNumberToObject(json_player, "strength", player->strength);
    cJSON_AddNumberToObject(json_player, "inventory_capacity", player->inventory_capacity);

    // Save player inventory
    cJSON *json_inventory = cJSON_CreateStringArray((const char **)player->inventory, player->inventory_count);
    cJSON_AddItemToObject(json_player, "inventory", json_inventory);

    cJSON_AddItemToObject(root, "player", json_player);

    // Save room data
    cJSON *json_rooms = cJSON_CreateArray();
    for (int i = 0; i < room_count; i++)
    {
        cJSON *json_room = cJSON_CreateObject();
        cJSON_AddStringToObject(json_room, "description", rooms[i].description);

        // Save room items
        cJSON *json_items = cJSON_CreateStringArray((const char **)rooms[i].items, rooms[i].item_count);
        cJSON_AddItemToObject(json_room, "items", json_items);

        // Save creature in room
        if (rooms[i].creature)
        {
            cJSON *json_creature = cJSON_CreateObject();
            cJSON_AddStringToObject(json_creature, "name", rooms[i].creature->name);
            cJSON_AddNumberToObject(json_creature, "health", rooms[i].creature->health);
            cJSON_AddNumberToObject(json_creature, "strength", rooms[i].creature->strength);
            cJSON_AddItemToObject(json_room, "creature", json_creature);
        }

        cJSON_AddItemToArray(json_rooms, json_room);
    }

    cJSON_AddItemToObject(root, "rooms", json_rooms);
    cJSON_AddNumberToObject(root, "currentRoomNumber", currentRoomNumber);

    char fileName[] = "game_state_XXXXXX";
    int fd = mkstemp(fileName);
    strcat(fileName, ".json");
    printf("The state saved: %s\n", fileName);

    FILE *file = fopen(fileName, "w");
    if (file)
    {
        char *json_data = cJSON_Print(root);
        fprintf(file, "%s", json_data);
        fclose(file);
        free(json_data);
    }

    cJSON_Delete(root);
}

// Function to read data from JSON
void load_game(const char *filename, Room *rooms, int *room_count, Player *player, int *currentRoomNumber)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);

    cJSON *root = cJSON_Parse(data);
    free(data);

    // Load player data
    cJSON *json_player = cJSON_GetObjectItem(root, "player");
    player->health = cJSON_GetObjectItem(json_player, "health")->valueint;
    player->strength = cJSON_GetObjectItem(json_player, "strength")->valueint;
    player->inventory_capacity = cJSON_GetObjectItem(json_player, "inventory_capacity")->valueint;

    cJSON *json_inventory = cJSON_GetObjectItem(json_player, "inventory");
    player->inventory_count = cJSON_GetArraySize(json_inventory);
    player->inventory = malloc(player->inventory_count * sizeof(char *));
    for (int i = 0; i < player->inventory_count; i++)
    {
        player->inventory[i] = strdup(cJSON_GetArrayItem(json_inventory, i)->valuestring);
    }

    // Load room data
    cJSON *json_rooms = cJSON_GetObjectItem(root, "rooms");
    *room_count = cJSON_GetArraySize(json_rooms);

    for (int i = 0; i < *room_count; i++)
    {
        cJSON *json_room = cJSON_GetArrayItem(json_rooms, i);
        rooms[i].description = strdup(cJSON_GetObjectItem(json_room, "description")->valuestring);

        cJSON *json_items = cJSON_GetObjectItem(json_room, "items");
        rooms[i].item_count = cJSON_GetArraySize(json_items);
        for (int j = 0; j < rooms[i].item_count; j++)
        {
            rooms[i].items[j] = strdup(cJSON_GetArrayItem(json_items, j)->valuestring);
        }

        cJSON *json_creature = cJSON_GetObjectItem(json_room, "creature");
        if (json_creature)
        {
            Creature *creature = malloc(sizeof(Creature));
            creature->name = strdup(cJSON_GetObjectItem(json_creature, "name")->valuestring);
            creature->health = cJSON_GetObjectItem(json_creature, "health")->valueint;
            creature->strength = cJSON_GetObjectItem(json_creature, "strength")->valueint;
            rooms[i].creature = creature;
        }
        else
        {
            rooms[i].creature = NULL;
        }
    }

    // Load current room number
    *currentRoomNumber = cJSON_GetObjectItem(root, "currentRoomNumber")->valueint;

    cJSON_Delete(root);
}

// Function to handle commands
void handle_command(const char *command, Player *player, Room **current_room, int *is_game_over, Room **roomList, int roomCount)
{
    if (strncmp(command, "save", 4) == 0)
    {
        save_game(*roomList, roomCount, player, ((*current_room)->description)[0] - '0');
    }

    else if (strncmp(command, "load", 4) == 0)
    {
        char filepath[256];
        if (sscanf(command + 5, "%255[^\n]", filepath) == 1)
        {
            FILE *file = fopen(filepath, "r");

            if (!file)
            {
                printf("Error: File '%s' not found. Please check the file path.\n", filepath);
            }
            else
            {
                fclose(file); // Dosya açılabiliyorsa kapat, işlemler için hazır.

                int *room_number = malloc(sizeof(int));
                if (!room_number)
                {
                    fprintf(stderr, "Memory allocation failed!\n");
                    exit(1);
                }

                // Oyun yükleme fonksiyonunu çağır
                load_game(filepath, *roomList, &roomCount, player, room_number);

                // Geçerli odayı güncelle
                *current_room = &(*roomList)[*room_number - 1];

                printf("Game '%s' loaded successfully!\n", filepath);

                // Bellek serbest bırakma
                free(room_number);
            }
        }
        else
        {
            printf("Use the load command correctly: load <filepath>\n");
        }
    }

    else if (strncmp(command, "move", 4) == 0)
    {
        char direction[16];
        if (sscanf(command + 5, "%s", direction) == 1)
        {
            int dir = -1; // Default direction to invalid
            if (strcmp(direction, "up") == 0)
                dir = 0;
            else if (strcmp(direction, "down") == 0)
                dir = 1;
            else if (strcmp(direction, "left") == 0)
                dir = 2;
            else if (strcmp(direction, "right") == 0)
                dir = 3;

            // Check if the specified direction is valid
            if (dir != -1 && (*current_room)->connections[dir] != NULL)
            {
                *current_room = (*current_room)->connections[dir];
                printf("You entered a new room: %s\n", (*current_room)->description);

                // Check if the player reached the final room
                if (strcmp((*current_room)->description, "11 This is a sunlit room. This is last room") == 0)
                {
                    int has_key = 0;
                    for (int i = 0; i < (player)->inventory_count; i++)
                    {
                        if (strcmp((player)->inventory[i], "key") == 0)
                        {
                            has_key = 1;
                            break;
                        }
                    }

                    if (has_key)
                    {
                        printf("Congratulations! You used the Key and successfully exited the dungeon. You win!\n");
                        *is_game_over = 1; // End the game
                    }
                    else
                    {
                        printf("You reached the last room, but you don't have the Key! Go back and find it.\n");
                    }
                }
            }

            else
            {
                printf("There is no exit in that direction!\n");
            }
        }
        else
        {
            printf("Use the move command correctly: move <direction>\n");
        }
    }
    else if (strcmp(command, "look") == 0)
    {
        printf("Room description: %s\n", (*current_room)->description);
        if ((*current_room)->item_count > 0)
        {
            printf("Items in this room:\n");
            for (int i = 0; i < (*current_room)->item_count; i++)
            {
                printf("- %s\n", (*current_room)->items[i]);
            }
        }
        if ((*current_room)->creature)
        {
            printf("There is a creature here: %s (Health: %d, Strength: %d)\n",
                   (*current_room)->creature->name,
                   (*current_room)->creature->health,
                   (*current_room)->creature->strength);
        }
    }
    else if (strcmp(command, "inventory") == 0)
    {
        printf("Your inventory:\n");
        for (int i = 0; i < (player)->inventory_count; i++)
        {
            printf("- %s\n", (player)->inventory[i]);
        }
        if ((player)->inventory_count == 0)
        {
            printf("Your inventory is empty.\n");
        }
    }
    else if (strncmp(command, "pickup", 6) == 0)
    {

        // Check if there's a creature in the room
        if ((*current_room)->creature)
        {
            printf("You cannot pick up items while %s is here. Defeat it first!\n",
                   (*current_room)->creature->name);
            return;
        }

        char item_name[64];
        if (sscanf(command + 7, "%63[^\n]", item_name) == 1)
        {
            int found = -1;

            // Search for the specified item in the room
            for (int i = 0; i < (*current_room)->item_count; i++)
            {
                if (strcmp((*current_room)->items[i], item_name) == 0)
                {
                    found = i;
                    break;
                }
            }
            if (found != -1)
            {
                // Add item to player's inventory if capacity allows
                if ((player)->inventory_count < (player)->inventory_capacity)
                {
                    (player)->inventory[(player)->inventory_count] = strdup((*current_room)->items[found]);
                    (player)->inventory_count++;
                    printf("You picked up: %s\n", item_name);

                    // Apply special effects based on item type
                    if (strcmp(item_name, "shield") == 0)
                    {
                        (player)->health += 10;
                        printf("You have equipped a shield and your health increases by 10. Your new health = %d", (player)->health);
                    }
                    else if (strcmp(item_name, "sword") == 0)
                    {
                        (player)->strength += 50;
                        printf("You have equipped a sword and your strength has increased by 50. Your new strength = %d", (player)->strength);
                    }
                    else if (strcmp(item_name, "armor") == 0)
                    {
                        (player)->health += 10;
                        (player)->strength += 10;
                        printf("You wore the armor and both your health and strength increased by 10. new health = %d, new  strength = %d", (player)->health, (player)->strength);
                    }

                    // Remove the item from the room
                    for (int i = found; i < (*current_room)->item_count - 1; i++)
                    {
                        (*current_room)->items[i] = (*current_room)->items[i + 1];
                    }
                    (*current_room)->item_count--;
                }
                else
                {
                    printf("Your inventory is full! You can't pick up more items.\n");
                }
            }
            else
            {
                printf("Item '%s' is not in this room.\n", item_name);
            }
        }
        else
        {
            printf("Use the pickup command correctly: pickup <item>\n");
        }
    }

    else if (strncmp(command, "drop", 4) == 0)
    {
        char item_name[64];
        if (sscanf(command + 5, "%63[^\n]", item_name) == 1)
        {
            int found = -1;
            for (int i = 0; i < (player)->inventory_count; i++)
            {
                if (strcmp((player)->inventory[i], item_name) == 0)
                {
                    found = i;
                    break;
                }
            }

            if (found != -1)
            {
                // Drop the item and add it to the current room
                add_item_to_room(*current_room, (player)->inventory[found]); // Gets copy
                printf("You dropped: %s\n", (player)->inventory[found]);

                // Remove item from inventory
                free((player)->inventory[found]); // Clear Memory
                for (int i = found; i < (player)->inventory_count - 1; i++)
                {
                    (player)->inventory[i] = (player)->inventory[i + 1];
                }
                (player)->inventory_count--;

                // Adjust player stats if the dropped item is a special item
                if (strcmp(item_name, "shield") == 0)
                {
                    (player)->health -= 10;
                    printf("You have equipped a shield and your health decreased by 10. Your new health = %d", (player)->health);
                }
                else if (strcmp(item_name, "sword") == 0)
                {
                    (player)->strength -= 50;
                    printf("You have equipped a sword and your strength has descreased by 50. Your new strength = %d", (player)->strength);
                }
                else if (strcmp(item_name, "armor") == 0)
                {
                    (player)->health -= 10;
                    (player)->strength -= 10;
                    printf("You took off the armor and both your health and strength decreased by 10. new health = %d, new  strength = %d", (player)->health, (player)->strength);
                }
            }
            else
            {
                printf("You don't have '%s' in your inventory.\n", item_name);
            }
        }
        else
        {
            printf("Use the drop command correctly: drop <item>\n");
        }
    }

    else if (strcmp(command, "list") == 0)
    {
        list_saved_games();
    }

    else if (strcmp(command, "attack") == 0)
    {
        if ((*current_room)->creature)
        {
            Creature *creature = (*current_room)->creature;
            printf("You engage in combat with %s!\n", creature->name);

            if ((player)->health > 0 && creature->health > 0)
            {

                // Player attacks
                creature->health -= (player)->strength;

                if (creature->health <= 0)
                {

                    printf("You attack %s for %d damage.%s's health is now 0 !!!\n You have defeated %s!\n",
                           creature->name, (player)->strength, creature->name, creature->name);
                    (*current_room)->creature = NULL; // Remove the creature from the room
                }
                else
                {
                    printf("You attack %s for %d damage. %s's health is now %d.\n",
                           creature->name, (player)->strength, creature->name, creature->health);

                    // Creature attacks
                    (player)->health -= creature->strength;

                    if ((player)->health <= 0)
                    {
                        printf("%s attacks you for %d damage.\nYou have been defeated by %s...\n",
                               creature->name, creature->strength, creature->name);
                        (player)->health = 0;

                        *is_game_over = 1; // Game over condition
                        return;
                    }
                    else
                    {
                        printf("%s attacks you for %d damage. Your health is now %d.\n",
                               creature->name, creature->strength, (player)->health);
                    }
                }
            }
        }
        else
        {
            printf("There is no creature here to attack.\n");
        }
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}
