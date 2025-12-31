#ifndef SPRITE_H
#define SPRITE_H

// Forward declaration for Atlas
typedef struct Atlas Atlas;

typedef struct {
    Atlas* atlas;
    int tile_id;
} Sprite;

#endif // SPRITE_H

