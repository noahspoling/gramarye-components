#include "textures/sprite_table.h"
#include "mem.h"
#include <string.h>

// Simple string comparison and hash functions
static int str_cmp(const void *x, const void *y) {
    return strcmp((const char*)x, (const char*)y);
}

static unsigned str_hash(const void *key) {
    const char *str = (const char*)key;
    unsigned hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

SpriteTable SpriteTable_new() {
    return Table_new(16, str_cmp, str_hash);
}

void SpriteTable_add(SpriteTable *spriteTable, const char *key, int spriteIndex) {
    char *keyCopy = Mem_alloc(strlen(key) + 1, __FILE__, __LINE__);
    strcpy(keyCopy, key);
    int *value = Mem_alloc(sizeof(int), __FILE__, __LINE__);
    *value = spriteIndex;
    Table_put(*spriteTable, keyCopy, value);
}

int SpriteTable_get(SpriteTable *spriteTable, const char *key) {
    int *value = Table_get(*spriteTable, key);
    return value ? *value : -1;
}

void SpriteTable_remove(SpriteTable *spriteTable, const char *key) {
    char *keyCopy = Mem_alloc(strlen(key) + 1, __FILE__, __LINE__);
    strcpy(keyCopy, key);
    int *value = Table_remove(*spriteTable, keyCopy);
    if (value) {
        Mem_free(value, __FILE__, __LINE__);
    }
    Mem_free(keyCopy, __FILE__, __LINE__);
}

void SpriteTable_free(SpriteTable *spriteTable) {
    Table_free(spriteTable);
}

