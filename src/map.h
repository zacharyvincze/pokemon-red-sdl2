#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tilemap.h"

class Map {
    public:
        Map();

        void fillMap(int tileID);

        void setTile(int x, int y, int tileID) { map[y][x] = tileID; }

        void setWidth(int w) { mWidth = w; }
        void setHeight(int h) { mHeight = h; }

        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        int getTile(int x, int y) { return map[y][x]; }
        int getSize() { return mTotalSize; }

        void draw(Graphics& graphics, Tilemap& tilemap, SDL_Rect& camera);

        void load(int map_id);

    private:
         std::vector<std::vector<int> > map;
         int mWidth;
         int mHeight;

         int mTotalSize;

         void resize();
         void clear();
         void insert(const int maptiles[]);
};

#endif // MAP_H
