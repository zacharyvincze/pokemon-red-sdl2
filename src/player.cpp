#include "player.h"
#include "constants.h"

Player::Player(Graphics& graphics, int x, int y, const std::string& file_path) :
    Entity(graphics, x, y, file_path) {

}

void Player::update(Map &map, std::map<std::string, NPC*> NPC) {
    _sprites[getSpriteID()]->update();
    
    if (_move_time > 0) {
        --_move_time;
        switch (_direction_facing) {
            case NORTH: _entity_rect.y -= _speed; break;
            case SOUTH: _entity_rect.y += _speed; break;
            case WEST: _entity_rect.x -= _speed; break;
            case EAST: _entity_rect.x += _speed; break;
        }
    }
    
    if (checkCollision(map) == 1) {
        switch (_direction_facing) {
            case NORTH: _entity_rect.y += _speed; break;
            case SOUTH: _entity_rect.y -= _speed; break;
            case WEST: _entity_rect.x += _speed; break;
            case EAST: _entity_rect.x -= _speed; break;
        }
        _move_time = 0;
    }
    
    if (checkCollision(map) == 2) {
        // When player is in grass
    }
}