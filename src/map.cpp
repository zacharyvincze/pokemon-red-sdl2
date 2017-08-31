#include "map.h"
#include "constants.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

// Initialize the  _map class
Map::Map(const std::string& map_path, Tileset& tileset) {
    
    mMapRect.w = 0;
    mMapRect.h = 0;
    mMapRect.x = 0;
    mMapRect.y = 0;
    mTotalSize = 0;
    
    _tileset = &tileset;
    
    std::ifstream stream(map_path.c_str(), std::ios::binary);
    char * signature;
    unsigned short map_width;
    unsigned short map_height;
    
    signature = new char [3];
    
    // Check if map file exsits
    if (!stream.is_open()) {
        printf("Failed to open map %s\n", map_path.c_str());
        exit(1);
    }
    
    // Get file size
    stream.seekg(0, std::ios::beg);
    int begin = stream.tellg();
    stream.seekg(0, std::ios::end);
    int end = stream.tellg();
    
    stream.seekg(0, std::ios::beg);
    stream.read(signature, 3);
    
    if (strcmp(signature, "MAP") != 0) {
        printf("Could not find MAP signature.\n");
        exit(1);
    }
    
    stream.read(reinterpret_cast<char *>(&map_width), sizeof(unsigned short));
    stream.read(reinterpret_cast<char *>(&map_height), sizeof(unsigned short));
    mMapRect.w = map_width;
    mMapRect.h = map_height;
    
    _map.resize(mMapRect.h);
    
    for (int y = 0; y < mMapRect.h; y++) {
        for (int x = 0; x < mMapRect.w; x++) {
            unsigned char tile_id;
            stream.read(reinterpret_cast<char *>(&tile_id), sizeof(unsigned char));
            _map[y].push_back(new Tile(tile_id, _tileset->getCollisionBuffer()[tile_id]));
        }
    }
    
    stream.close();
    delete(signature);
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
