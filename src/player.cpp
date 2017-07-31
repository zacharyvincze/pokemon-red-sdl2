#include "player.h"

Player::Player(Graphics& graphics, int x, int y, const std::string& file_path) :
    Entity(graphics, x, y, file_path) {

}

void Player::update(Map &map, std::vector<NPC*> NPCs) {
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
    
    _current_tile = map.getTile(_entity_rect.x / 16, _entity_rect.y / 16)->getTileID();
    
    if (checkCollision(map)) {
        switch (_direction_facing) {
            case NORTH: _entity_rect.y += _speed; break;
            case SOUTH: _entity_rect.y -= _speed; break;
            case WEST: _entity_rect.x += _speed; break;
            case EAST: _entity_rect.x -= _speed; break;
        }
    }
}