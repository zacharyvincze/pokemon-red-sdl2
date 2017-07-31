#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tileset.h"

class Map {
    public:
        Map(const std::string& file_path, const int width, const int height);

        SDL_Rect& getMapRect() { return mMapRect; }
        std::vector<std::vector<int> > getMap() { return _map; }
        
        int getTile(int x, int y) { return _map[y][x]; }
        
        void draw(Graphics& graphics, Tileset& tileset, SDL_Rect& camera);

    private:
         std::vector<std::vector<int> > _map;

         int mTotalSize;
         SDL_Rect mMapRect;
};

#endif // MAP_H
