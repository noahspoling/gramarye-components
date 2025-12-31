#include "core/map.h"
#include <stdlib.h>
#include <string.h>

Map* create_map(int width, int height) {
    Map* map = (Map*)malloc(sizeof(Map));
    map->width = width;
    map->height = height;
    map->tiles = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        map->tiles[i] = (char*)malloc(width * sizeof(char));
        memset(map->tiles[i], ' ', width);
    }
    return map;
}

void destroy_map(Map* map) {
    if (map) {
        if (map->tiles) {
            for (int i = 0; i < map->height; i++) {
                free(map->tiles[i]);
            }
            free(map->tiles);
        }
        free(map);
    }
}

void set_tile(Map* map, int x, int y, char tile) {
    if (map && map->tiles && x >= 0 && x < map->width && y >= 0 && y < map->height) {
        map->tiles[y][x] = tile;
    }
}

char get_tile(const Map* map, int x, int y) {
    if (map && map->tiles && x >= 0 && x < map->width && y >= 0 && y < map->height) {
        return map->tiles[y][x];
    }
    return ' ';
}

