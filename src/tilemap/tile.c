#include "tilemap/tile.h"
#include <stdlib.h>

Tile* Tile_new(uint16_t tile_id, uint8_t flags) {
    Tile* tile = (Tile*)malloc(sizeof(Tile));
    tile->tile_id = tile_id;
    tile->flags = flags;
    return tile;
}

void Tile_set_flag(Tile* tile, uint8_t flag) {
    if (tile) {
        tile->flags |= flag;
    }
}

void Tile_clear_flag(Tile* tile, uint8_t flag) {
    if (tile) {
        tile->flags &= ~flag;
    }
}

bool Tile_has_flag(const Tile* tile, uint8_t flag) {
    return tile && (tile->flags & flag) != 0;
}
