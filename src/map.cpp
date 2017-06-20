/**
    map.cpp
    Purpose: Manages maps in the game

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "map.h"

#include "data/maps/pallet_town.cpp"
#include "data/maps/viridian_city.cpp"

#include "constants.cpp"

#include "data/tiles.cpp"

// Initialize the map class
Map::Map() {
    mWidth = 0;
    mHeight = 0;
    mTotalSize = 0;
}

// Fill the map with whatever tileID was specified
void Map::fillMap(int tileID) {
    for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mWidth; j++) {
            map[i][j] = tileID;
        }
    }
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
void Map::draw(Graphics& graphics, Tilemap& tilemap, SDL_Rect& camera) {
    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mHeight; j++) {
            tilemap.draw(graphics, -camera.x + (i * 16), -camera.y + (j * 16), map[j][i]);
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

void Map::load(int map_id) {
    switch(map_id) {
        case MapConst::PALLET_TOWN: {
            mWidth = pallet_town::MAP_WIDTH;
            mHeight = pallet_town::MAP_HEIGHT;
            mTotalSize = pallet_town::MAP_HEIGHT * pallet_town::MAP_WIDTH;
            insert(pallet_town::MAP_TILES);
        }
        break;
        case MapConst::VIRIDIAN_CITY: {
            mWidth = viridian_city::MAP_WIDTH;
            mHeight = viridian_city::MAP_HEIGHT;
            mTotalSize = viridian_city::MAP_HEIGHT * viridian_city::MAP_WIDTH;
            insert(viridian_city::MAP_TILES);
        }
        break;
    }
}
