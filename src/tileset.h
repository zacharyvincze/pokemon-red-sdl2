#ifndef TILESET_H
#define TILESET_H

#include "graphics.h"

#include <string>
#include <vector>

class Tileset {
    public:
        Tileset(Graphics& graphics, const std::string file_path, const std::string collision_path);
        ~Tileset();

        void draw(Graphics& graphics, int x, int y, int tileID);
        
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        
        std::vector<unsigned char> getCollisionBuffer() { return _collision_buffer; }

    private:
        SDL_Texture* mTilesheet;
        std::vector<SDL_Rect> mTileClips;
        
        std::vector<unsigned char> _collision_buffer;

        int mWidth;
        int mHeight;
};

#endif // TILE_H
