/**
    tilemap.cpp
    Purpose: Creates a tileset from an image

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "tileset.h"

namespace {
    const int tileSize = 16;
}

// Initailize the tilemap class
Tileset::Tileset(Graphics& graphics, const std::string file_path) {
    mWidth = 0;
    mHeight = 0;
    mTilesheet = graphics.loadImage(file_path);                    // Load selected tileset
    SDL_QueryTexture(mTilesheet, NULL, NULL, &mWidth, &mHeight);  // Get image height and width
    mTileClips.resize((mWidth / tileSize) * (mHeight / tileSize));          // Resize the tileset vector to the image height and width

    int k = 0;

    for (int i = 0; i < (mHeight / tileSize); i++) {      // Cycles through the image and creates cutouts
        for (int j = 0; j < (mWidth / tileSize); j++) {   // Each tile has a specified ID
            mTileClips[k].x = j * tileSize;               // Set tile x
            mTileClips[k].y = i * tileSize;               // Set tile y
            mTileClips[k].w = tileSize;                   // Standard tile width and height are 8 pixels
            mTileClips[k].h = tileSize;
            k++;
        }
    }
}

Tileset::~Tileset() {
    SDL_DestroyTexture(mTilesheet);
}

// Draw a single tile
void Tileset::draw(Graphics& graphics, int x, int y, int tileID) {
    SDL_Rect destinationRectangle;                                          // Rectagle, where to draw to the screen
    destinationRectangle.x = x;                                             // Set destination rectangle X
    destinationRectangle.y = y;                                             // Set destination rectangle Y
    graphics.render(mTilesheet, &mTileClips[tileID], &destinationRectangle);  // Render the tile
}
