/**
    map.cpp
    Purpose: Manages maps in the game

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "map.h"
#include "constants.cpp"

namespace {
    const int tileSize = 16;
}

// Initialize the map class
Map::Map() {
    mWidth = 0;
    mHeight = 0;
    mTotalSize = 0;
}

// Resize the map vector to mHeight and mWidth
void Map::resize() {
    map.resize(mHeight);

    for (int i = 0; i < mHeight; i++) {
        map[i].resize(mWidth);
    }
}

// Set all tiles of the map to 0
void Map::clear() {
    for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mWidth; j++) {
            map[i][j] = 0;
        }
    }
}

// Draw the map using the tilset
void Map::draw(Graphics& graphics, Tileset& tileset, SDL_Rect& camera) {
    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mHeight; j++) {
            tileset.draw(graphics, -camera.x + (i * tileSize), -camera.y + (j * tileSize), map[j][i]);
        }
    }
}

void Map::insert(const int maptiles[]) {
    resize();
    clear();
    int k = 0;
    for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mWidth; j++) {
            map[i][j] = maptiles[k];
            k++;
        }
    }
}

void Map::load(const int map_tiles[], const int width, const int height) {
    mWidth = width;
    mHeight = height;
    insert(map_tiles);
}
