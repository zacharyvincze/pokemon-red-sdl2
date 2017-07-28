#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tileset.h"

class Map {
    public:
        Map();

        void setTile(int x, int y, int tileID) { map[y][x] = tileID; }

        SDL_Rect& getMapRect() { return mMapRect; }

        void draw(Graphics& graphics, Tileset& tileset, SDL_Rect& camera);

        void load(const int map_tiles[], const int width, const int height);

    private:
         std::vector<std::vector<int> > map;

         int mTotalSize;
         SDL_Rect mMapRect;

         void resize();
         void clear();
         void insert(const int maptiles[]);
};

#endif // MAP_H
