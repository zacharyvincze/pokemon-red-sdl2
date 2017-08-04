#include "tile.h"
#include "constants.h"

Tile::Tile(int tile_id, int is_wall) {
    _is_wall = is_wall;
    _tile_id = tile_id;
}

Tile::~Tile() {
    _tile_id = 0;
    _is_wall = 0;
}