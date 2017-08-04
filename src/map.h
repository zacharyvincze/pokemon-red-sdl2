#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tileset.h"
#include "tile.h"

class Map {
    public:
        Map(const std::string& map_path, const std::string& col_path, Tileset& tileset, const int width, const int height);
        ~Map();

        SDL_Rect& getMapRect() { return mMapRect; }
        std::vector<std::vector<Tile*> > getMap() { return _map; }
        
        void draw(Graphics& graphics, SDL_Rect& camera);

    private:
         std::vector<std::vector<Tile*> > _map;
         bool checkCollision(int x, int y, SDL_Rect camera);
         
         Tileset* _tileset;

         int mTotalSize;
         SDL_Rect mMapRect;
};

#endif // MAP_H
