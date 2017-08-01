/**
     _map.cpp
    Purpose: Manages maps in the game

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "map.h"
#include "constants.h"
#include "SDL2/SDL.h"
#include <stdio.h>

// Initialize the  _map class
Map::Map(const std::string& file_path, const int width, const int height) {
    
    mMapRect.w = width;
    mMapRect.h = height;
    mMapRect.x = 0;
    mMapRect.y = 0;
    mTotalSize = 0;
    
    _map.resize(mMapRect.h);
    
    FILE *fp;
    
    fp = fopen(file_path.c_str(), "rb");
    
    if (fp == NULL) {
        printf("Failed to open map %s\n", file_path.c_str());
        exit(1);
    }
    
    for (int y = 0; y < mMapRect.h; y++) {
        for (int x = 0; x < mMapRect.w; x++) {
            int tile_id;
            fscanf(fp, "%d", &tile_id);
            _map[y].push_back(new Tile(x * Constants::TILE_SIZE, y * Constants::TILE_SIZE, tile_id));
        }
    }
    
    fclose(fp);
}

// Draw the  _map using the tilset
void Map::draw(Graphics& graphics, Tileset& tileset, SDL_Rect& camera) {
    for (int i = 0; i < mMapRect.w; i++) {
        for (int j = 0; j < mMapRect.h; j++) {
            if (checkCollision(_map[j][i]->getTileRect(), camera))
                tileset.draw(graphics, -camera.x + (_map[j][i]->getTileRect().x), -camera.y + (_map[j][i]->getTileRect().y),  _map[j][i]->getTileID());
        }
    }
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;
    
    return true;
}
