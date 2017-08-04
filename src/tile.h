#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

class Tile {
    public:
        Tile(int tile_id, int is_wall);
        ~Tile();
        int getTileID() { return _tile_id; }
        int isWall() { return _is_wall; }
        
    private:
        int _tile_id;
        int _is_wall;
};

#endif // TILE_H