#ifndef TILE_H
#define TILE_H

#include "graphics.h"

#include <string>
#include <vector>

class Tilemap {
    public:
        enum ETile {
                GROUND_EMPTY,           // 0
                GROUND_GRASS_PARTIAL,   // 1
                GROUND_GRASS_FULL,      // 2
                GROUND_SAND,            // 3
                OBJECT_SIGN_HANGING,    // 4
                OBJECT_SIGN_STANDING,   // 5
                OBJECT_BARRIER_LARGE,   // 6
                OBJECT_BARRIER_SMALL,   // 7
                GROUND_WILDGRASS,       // 8
                GROUND_WEED_1,          // 9
                GROUND_WEED_2,          // 10
                FLOOR_BRICK,            // 11
                FLOOR_WOOD,             // 12
                FLOOR_CARPET,           // 13
                NATURE_TREE_1,          // 14
                NATURE_TREE_CUTTABLE,   // 15
                CAVE_EXTERIOR_TOP_LEFT_EMPTY,   // 16
                CAVE_EXTERIOR_TOP_CENTER,       // 17
                CAVE_EXTERIOR_TOP_RIGHT_EMPTY,  // 18
                CAVE_EXTERIOR_TOP_RIGHT_SAND,   // 19
                CAVE_EXTERIOR_TOP_RIGHT_GRASS,  // 20
                EMPTY,                  // 21
                NATURE_TREE_2,          // 22
                NATURE_ROCK,            // 23
        };

        Tilemap();

        SDL_Rect getTileClip(int clip) { return mTileClips[clip]; }
        SDL_Texture* getTilemap() { return mTilemap; }

        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }

        void draw(Graphics& graphics, int x, int y, int tileID);
        void load(Graphics& graphics, const std::string filePath);

    private:
        SDL_Texture* mTilemap;
        std::vector<SDL_Rect> mTileClips;

        int mWidth;
        int mHeight;
};

#endif // TILE_H
