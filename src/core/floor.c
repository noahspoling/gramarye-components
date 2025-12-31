#include "core/floor.h"
#include "mem.h"
#include <stddef.h>

Floor *Floor_create(unsigned int level) {
    Floor *floor = Mem_alloc(sizeof(Floor), __FILE__, __LINE__);
    floor->level = level;
    floor->rooms = Table_new(16, NULL, NULL); // TODO: Add proper comparison/hash functions
    floor->connections = Array_new(0, sizeof(Connection));
    floor->current_room = NULL;
    floor->floor_keys = Array_new(0, sizeof(Key));
    return floor;
}

void Floor_destroy(Floor *floor) {
    if (floor) {
        Table_free(&floor->rooms);
        Array_free(&floor->connections);
        Array_free(&floor->floor_keys);
        Mem_free(floor, __FILE__, __LINE__);
    }
}

