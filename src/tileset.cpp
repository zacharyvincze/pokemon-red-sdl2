#include "tileset.h"
#include "constants.h"

#include <fstream>

Tileset::Tileset(Graphics& graphics, const std::string file_path, const std::string collision_path) {
    mWidth = 0;
    mHeight = 0;
    mTilesheet = graphics.loadImage(file_path);
    
    SDL_QueryTexture(mTilesheet, NULL, NULL, &mWidth, &mHeight);
    
    std::ifstream stream (collision_path.c_str(), std::ios::binary);
    char * signature;
    signature = new char [3];
    
    if (!stream.is_open()) {
        printf("Failed to open %s\n", collision_path.c_str());
        exit(1);
    }
    
    stream.seekg(0, std::ios::beg);
    int begin = stream.tellg();
    stream.seekg(0, std::ios::end);
    int end = stream.tellg();
    
    stream.seekg(0, std::ios::beg);
    stream.read(signature, 3);
    
    if (strcmp(signature, "COL") != 0) {
        printf("Incorrect file format.\n");
        exit(1);
    }
    
    delete(signature);
    
    stream.ignore(1);
    
    for (int i = 0; i < (end - begin) - 4; i++) {
        unsigned char tile_id;
        stream.read(reinterpret_cast<char *>(&tile_id), sizeof(unsigned char));
        printf("%d", tile_id);
        _collision_buffer.push_back(tile_id);
    }
    
    stream.close();

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
