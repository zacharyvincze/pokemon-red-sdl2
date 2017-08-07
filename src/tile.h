#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

class Tile {
    public:
        Tile(unsigned char tile_id, unsigned char is_wall);
        ~Tile();
        unsigned char getTileID() { return _tile_id; }
        unsigned char isWall() { return _is_wall; }
        
    private:
        unsigned char _tile_id;
        unsigned char _is_wall;
};

#endif // TILE_H