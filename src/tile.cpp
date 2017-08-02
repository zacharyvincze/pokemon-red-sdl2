#include "tile.h"
#include "constants.h"

Tile::Tile(int x, int y, int tile_id, int is_wall) {
    _is_wall = is_wall;
    _tile_id = tile_id;
    _tile_rect.x = x;
    _tile_rect.y = y;
    _tile_rect.w = Constants::TILE_SIZE;
    _tile_rect.h = Constants::TILE_SIZE;
}

Tile::~Tile() {
    _tile_id = 0;
}