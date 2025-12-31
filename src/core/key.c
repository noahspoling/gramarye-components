#include "core/key.h"
#include <stdlib.h>

void init_key(Key* key, KeyType type, int id) {
    if (key) {
        key->type = type;
        key->id = id;
    }
}

void free_key(Key* key) {
    // Key is a simple struct, no dynamic memory to free
    // This function is kept for API consistency
    (void)key;
}

