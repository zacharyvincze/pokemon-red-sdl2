#include "tileset.h"
#include "constants.h"

Tileset::Tileset(Graphics& graphics, const std::string file_path, const std::string collision_path) {
    mWidth = 0;
    mHeight = 0;
    _collision_filepath = collision_path;
    mTilesheet = graphics.loadImage(file_path);
    
    SDL_QueryTexture(mTilesheet, NULL, NULL, &mWidth, &mHeight);

    for (int y = 0; y < (mHeight / Constants::TILE_SIZE); y++) {
        for (int x = 0; x < (mWidth / Constants::TILE_SIZE); x++) {
            SDL_Rect source_rectangle;
            source_rectangle.x = x * Constants::TILE_SIZE;
            source_rectangle.y = y * Constants::TILE_SIZE;
            source_rectangle.w = Constants::TILE_SIZE;
            source_rectangle.h = Constants::TILE_SIZE;
            mTileClips.push_back(source_rectangle);
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
