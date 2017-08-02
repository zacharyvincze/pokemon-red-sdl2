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
Map::Map(const std::string& map_path, const std::string& col_path, Tileset& tileset, const int width, const int height) {
    
    mMapRect.w = width;
    mMapRect.h = height;
    mMapRect.x = 0;
    mMapRect.y = 0;
    mTotalSize = 0;
    
    _tileset = &tileset;
    
    FILE *map_file;
    FILE *col_file;
    std::vector<int> col_buffer;
    
    map_file = fopen(map_path.c_str(), "rb");
    col_file = fopen(col_path.c_str(), "rb");
    
    if (map_file == NULL) {
        printf("Failed to open map %s\n", map_path.c_str());
        exit(1);
    }
    
    if (col_file == NULL) {
        printf("Failed to open col file %s\n", col_path.c_str());
        exit(1);
    }
    
    for (int i = 0; i < (_tileset->getWidth() / 8) * (_tileset->getHeight() / 8); i++) {
        int tile_id;
        fscanf(col_file, "%d", &tile_id);
        col_buffer.push_back(int(tile_id));
    }
    
    for (int y = 0; y < mMapRect.h; y++) {
        for (int x = 0; x < mMapRect.w; x++) {
            int tile_id;
            fscanf(map_file, "%d", &tile_id);
            _map.push_back(new Tile(x * Constants::TILE_SIZE, y * Constants::TILE_SIZE, tile_id, col_buffer[tile_id]));
        }
    }
    
    fclose(map_file);
    fclose(col_file);
}

Map::~Map() {
    for (std::vector<Tile*>::iterator i = _map.begin(); i != _map.end(); i++) {
        delete (*i);
    }
}

// Draw the  _map using the tilset
void Map::draw(Graphics& graphics, SDL_Rect& camera) {
    for (int i = 0; i < _map.size(); i++) {
        if (checkCollision(_map[i]->getTileRect(), camera))
            _tileset->draw(graphics, -camera.x + (_map[i]->getTileRect().x), -camera.y + (_map[i]->getTileRect().y),  _map[i]->getTileID());
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
