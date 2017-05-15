/**
    map.cpp
    Purpose: Manages maps in the game

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "map.h"

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

// Load the map
void Map::load(int mapID) {

    clear();

    // Load different map configurations based on mapID given
    switch (mapID) {
        // TODO: Figure out a cleaner way to create maps
        case PALETTE_TOWN: {
            mWidth = 20;
            mHeight = 18;
            mTotalSize = mWidth * mHeight;

            resize();

            int k = 0;

            int temp[360] = {
                  8,  8,  8,  6,  8,  8,  8,  8,  8,  6,  9,  9,  6,  8,  8,  8,  8,  8,  6,  8,
                  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  9,  9,  6,  6,  6,  6,  6,  6,  6,  6,
                  6,  8,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  8,  6,
                  6,  8,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  8,  6,
                  6,  8,  2,  2,  1,  0,  1,  0,  1,  0,  2,  2,  1,  0,  1,  0,  1,  0,  8,  6,
                  6,  8,  2,  4,  0,  1,  0,  1,  0,  1,  2,  4,  0,  1,  0,  1,  0,  1,  8,  6,
                  6,  8,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  8,  6,
                  6,  8,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  8,  6,
                  6,  8,  1,  0,  2,  2,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  6,
                  6,  6,  8,  8,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6
            };

            for (int i = 0; i < mHeight; i++) {
                for (int j = 0; j < mWidth; j++) {
                    map[i][j] = temp[k];
                    k++;
                }
            }

            break;
        }

        case ROUTE_1:
            mWidth = 10;
            mHeight = 9;

            resize();

            break;
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

    for (int i = 0; i < map.size(); i++) {
        map[i].resize(0);
    }

    map.resize(0);

    mHeight = 0;
    mWidth = 0;
}

// Draw the map using the tilset
void Map::draw(Graphics& graphics, Tilemap& tilemap, int cameraX, int cameraY) {
    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mHeight; j++) {
            tilemap.draw(graphics, -cameraX + (i * 16), -cameraY + (j * 16), map[j][i]);
        }
    }
}
