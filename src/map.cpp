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
    mMapRect.w = 0;
    mMapRect.h = 0;
    mMapRect.x = 0;
    mMapRect.y = 0;
    mTotalSize = 0;
}

// Resize the map vector to mMapRect.h and mMapRect.w
void Map::resize() {
    map.resize(mMapRect.h);

    for (int i = 0; i < mMapRect.h; i++) {
        map[i].resize(mMapRect.w);
    }
}

// Set all tiles of the map to 0
void Map::clear() {
    for (int i = 0; i < mMapRect.h; i++) {
        for (int j = 0; j < mMapRect.w; j++) {
            map[i][j] = 0;
        }
    }
}

// Draw the map using the tilset
void Map::draw(Graphics& graphics, Tileset& tileset, SDL_Rect& camera) {
    for (int i = 0; i < mMapRect.w; i++) {
        for (int j = 0; j < mMapRect.h; j++) {
            tileset.draw(graphics, -camera.x + (i * tileSize), -camera.y + (j * tileSize), map[j][i]);
        }
    }
}

void Map::insert(const int maptiles[]) {
    resize();
    clear();
    int k = 0;
    for (int i = 0; i < mMapRect.h; i++) {
        for (int j = 0; j < mMapRect.w; j++) {
            map[i][j] = maptiles[k];
            k++;
        }
    }
}

void Map::load(const int map_tiles[], const int width, const int height) {
    mMapRect.w = width;
    mMapRect.h = height;
    insert(map_tiles);
}
