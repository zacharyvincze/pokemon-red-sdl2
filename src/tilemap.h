#ifndef TILE_H
#define TILE_H

#include "graphics.h"

#include <string>
#include <vector>

class Tilemap {
    public:
        Tilemap(Graphics& graphics, const std::string file_path);
        ~Tilemap();

        SDL_Rect getTileClip(int clip) { return mTileClips[clip]; }
        SDL_Texture* getTilemap() { return mTilemap; }

        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }

        void draw(Graphics& graphics, int x, int y, int tileID);

    private:
        SDL_Texture* mTilemap;
        std::vector<SDL_Rect> mTileClips;

        int mWidth;
        int mHeight;
};

#endif // TILE_H
