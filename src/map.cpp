/**
    map.cpp
    Purpose: Manages maps in the game

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "map.h"

#include "data/maps/pallettown.cpp"
#include "data/maps/route_1.cpp"

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
        case PALLET_TOWN: {
            mWidth = pallettown::MAP_WIDTH;
            mHeight = pallettown::MAP_HEIGHT;
            mTotalSize = pallettown::MAP_HEIGHT * pallettown::MAP_WIDTH;
            insert(pallettown::MAP_TILES);
        }
        break;
        case ROUTE_1: {
            mWidth = route_1::MAP_WIDTH;
            mHeight = route_1::MAP_HEIGHT;
            mTotalSize = route_1::MAP_HEIGHT * route_1::MAP_WIDTH;
            insert(route_1::MAP_TILES);
        }
        break;
    }
}
