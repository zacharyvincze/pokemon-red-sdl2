/**
    tilemap.cpp
    Purpose: Creates a tileset from an image

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "tilemap.h"

// Initailize the tilemap class
Tilemap::Tilemap() {
    mWidth = 0;
    mHeight = 0;
}

// Load the tilemap from a png image file
void Tilemap::load(Graphics& graphics, const std::string filePath) {
    mTilemap = graphics.loadImage(filePath);                    // Load selected tileset
    SDL_QueryTexture(mTilemap, NULL, NULL, &mWidth, &mHeight);  // Get image height and width
    mTileClips.resize((mWidth / 16) * (mHeight / 16));          // Resize the tileset vector to the image height and width

    int k = 0;

    for (int i = 0; i < (mHeight / 16); i++) {      // Cycles through the image and creates cutouts
        for (int j = 0; j < (mWidth / 16); j++) {   // Each tile has a specified ID
            mTileClips[k].x = j * 16;               // Set tile x
            mTileClips[k].y = i * 16;               // Set tile y
            mTileClips[k].w = 16;                   // Standard tile width and height are 16 pixels
            mTileClips[k].h = 16;
            k++;
        }
    }
}

// Draw a single tile
void Tilemap::draw(Graphics& graphics, int x, int y, int tileID) {
    SDL_Rect destinationRectangle;                                          // Rectagle, where to draw to the screen
    destinationRectangle.x = x;                                             // Set destination rectangle X
    destinationRectangle.y = y;                                             // Set destination rectangle Y
    graphics.render(mTilemap, &mTileClips[tileID], &destinationRectangle);  // Render the tile
}
