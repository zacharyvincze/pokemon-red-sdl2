#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

class Tile {
    public:
        Tile(int x, int y, int tile_id, int is_wall);
        ~Tile();
        SDL_Rect& getTileRect() { return _tile_rect; }
        int getTileID() { return _tile_id; }
        int isWall() { return _is_wall; }
        
    private:
        SDL_Rect _tile_rect;
        int _tile_id;
        int _is_wall;
};

#endif // TILE_H