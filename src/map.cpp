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
    
    // Check if map file exsits
    if (map_file == NULL) {
        printf("Failed to open map %s\n", map_path.c_str());
        exit(1);
    }
    
    // Check if collision file exists
    if (col_file == NULL) {
        printf("Failed to open col file %s\n", col_path.c_str());
        exit(1);
    }
    
    for (int i = 0; i < (_tileset->getWidth() / 8) * (_tileset->getHeight() / 8); i++) {
        int tile_id;
        fscanf(col_file, "%d", &tile_id);
        col_buffer.push_back(int(tile_id));
    }
    
    _map.resize(mMapRect.h);
    
    for (int y = 0; y < mMapRect.h; y++) {
        for (int x = 0; x < mMapRect.w; x++) {
            int tile_id;
            fscanf(map_file, "%d", &tile_id);
            _map[y].push_back(new Tile(tile_id, col_buffer[tile_id]));
        }
    }
    
    fclose(map_file);
    fclose(col_file);
}

Map::~Map() {
    for (int y = 0; y < _map.size(); y++) {
        for (int x = 0; x < _map[y].size(); x++) {
            delete _map[y][x];
        }
    }
}

// Draw the  _map using the tilset
void Map::draw(Graphics& graphics, SDL_Rect& camera) {
    for (int y = 0; y < _map.size(); y++) {
        for (int x = 0; x < _map[y].size(); x++) {
            if (checkCollision(x, y, camera))
                _tileset->draw(graphics, -camera.x + (x * Constants::TILE_SIZE), -camera.y + (y * Constants::TILE_SIZE),  _map[y][x]->getTileID());
        }
    }
}

bool Map::checkCollision(int x, int y, SDL_Rect camera) {
    if ((y + 1) * Constants::TILE_SIZE <= camera.y) return false;
    if (y * Constants::TILE_SIZE >= camera.y + camera.h) return false;
    if ((x + 1) * Constants::TILE_SIZE <= camera.x) return false;
    if (x * Constants::TILE_SIZE >= camera.x + camera.w) return false;
    
    return true;
}
