#ifndef ATLAS_H
#define ATLAS_H

#include "table.h"
#include "except.h"

#define ATLAS_MAX_CAPACITY 500
#define ATLAS_INITIAL_CAPACITY 400

typedef Table_T Atlas_Table;

extern const Except_T Atlas_Uninitialized_Error;
extern const Except_T Atlas_Capacity_Error;

// Forward declaration - full definition with raylib types in gramarye-component-functions
// Systems that need full access should include gramarye-component-functions/textures/atlas.h
typedef struct Atlas Atlas;

// Function declarations (implementations in gramarye-component-functions)
Atlas* Atlas_new(int initialCapacity);
void Atlas_setTexture(Atlas* atlas, char *path);
void Atlas_removeRect(Atlas* atlas, int index);
void Atlas_clear(Atlas* atlas);
int Atlas_getRectCount(const Atlas* atlas);
void Atlas_free(Atlas* atlas);

// Note: Atlas_addRect and Atlas_getRect require raylib Rectangle type
// Include gramarye-component-functions/textures/atlas.h for full API

#endif // ATLAS_H
