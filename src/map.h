#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tileset.h"
#include "tile.h"

class Map {
    public:
        Map(const std::string& file_path, const int width, const int height);
        ~Map();

        SDL_Rect& getMapRect() { return mMapRect; }
        std::vector<Tile*> getMap() { return _map; }
        
        void draw(Graphics& graphics, Tileset& tileset, SDL_Rect& camera);

    private:
         std::vector<Tile*> _map;
         bool checkCollision(SDL_Rect a, SDL_Rect b);

         int mTotalSize;
         SDL_Rect mMapRect;
};

#endif // MAP_H
