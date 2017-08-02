#ifndef TILESET_H
#define TILESET_H

#include "graphics.h"

#include <string>
#include <vector>

class Tileset {
    public:
        Tileset(Graphics& graphics, const std::string file_path);
        ~Tileset();

        void draw(Graphics& graphics, int x, int y, int tileID);
        
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }

    private:
        SDL_Texture* mTilesheet;
        std::vector<SDL_Rect> mTileClips;

        int mWidth;
        int mHeight;
};

#endif // TILE_H
