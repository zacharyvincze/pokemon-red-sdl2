/**
    player.cpp
    Purpose: Manage player logic and sprites

    @author: Zachary Vincze
    @version: 28/05/2017
*/

#include "player.h"
#include "game.h"

namespace {
    const float walkSpeed = 1;             // Pixles moved per frame
    const int playerFrame = 0;

    const int verticalDrawOffset = 4;

    const int numWalkFrames = 4;
    const int numSidewayWalkFrames = 2;
    const int walkFps = 10;                // Change frames after certain amount of frames have passed
}

Player::Player(Graphics& graphics, int x, int y, const std::string& file_path) {
    _player_rect.x = x * 16;
    _player_rect.y = y * 16;
    _player_rect.w = 16;
    _player_rect.h = 16;
    
    _move_time = 0;
    _frames_to_cross_one_tile = 16;
    _speed = 16 / _frames_to_cross_one_tile;

    _direction_facing = RIGHT;
    _motion_type = WALKING;

    // Load sprites
    // ----- STATIC SPRITES
    _sprites.push_back(new Sprite(graphics, file_path, 0, 0, Game::kTileSize, Game::kTileSize));
    _sprites.push_back(new Sprite(graphics, file_path, 0, Game::kTileSize, Game::kTileSize, Game::kTileSize));
    _sprites.push_back(new Sprite(graphics, file_path, 0, Game::kTileSize * 2, Game::kTileSize, Game::kTileSize));
    _sprites.push_back(new Sprite(graphics, file_path, 0, Game::kTileSize * 3, Game::kTileSize, Game::kTileSize));

    // ----- ANIMATED SPRITES
    _sprites.push_back(new AnimatedSprite(graphics, file_path, 0, 0, Game::kTileSize, Game::kTileSize, walkFps, numWalkFrames));
    _sprites.push_back(new AnimatedSprite(graphics, file_path, 0, Game::kTileSize, Game::kTileSize, Game::kTileSize, walkFps, numWalkFrames));
    _sprites.push_back(new AnimatedSprite(graphics, file_path, 0, Game::kTileSize * 2, Game::kTileSize, Game::kTileSize, walkFps, numSidewayWalkFrames));
    _sprites.push_back(new AnimatedSprite(graphics, file_path, 0, Game::kTileSize * 3, Game::kTileSize, Game::kTileSize, walkFps, numSidewayWalkFrames));
}

Player::~Player() {
    for (std::vector<Sprite*>::iterator i = _sprites.begin(); i != _sprites.end(); i++) {
        delete (*i);
    }
}

void Player::update(SDL_Rect& mapRect) {
    _sprites[getSpriteID()]->update();
    
    if (_move_time > 0) {
        --_move_time;
        switch (_direction_facing) {
            case UP: _player_rect.y -= _speed; break;
            case DOWN: _player_rect.y += _speed; break;
            case LEFT: _player_rect.x -= _speed; break;
            case RIGHT: _player_rect.x += _speed; break;
        }
    }
    
    // Map collision detection
    if (_player_rect.x < 0) _player_rect.x = 0;
    if (_player_rect.x > (mapRect.w - 1) * 16) _player_rect.x = (mapRect.w - 1) * 16;
    if (_player_rect.y < 0) _player_rect.y = 0;
    if (_player_rect.y > (mapRect.h - 1) * 16) _player_rect.y = (mapRect.h - 1) * 16;
}

void Player::draw(Graphics& graphics, SDL_Rect& camera) {
    // Drawing with the 4 pixel y offset from the original game
    _sprites[getSpriteID()]->draw(graphics, _player_rect.x - camera.x, (_player_rect.y - verticalDrawOffset) - camera.y);
}

int Player::getSpriteID() {

    if (_move_time > 0) {
        _motion_type = WALKING;
    } else {
        _motion_type = STANDING;
    }

    if (_direction_facing == UP && _motion_type == STANDING)
        return 0;
    else if (_direction_facing == DOWN && _motion_type == STANDING)
        return 1;
    else if (_direction_facing == LEFT && _motion_type == STANDING)
        return 2;
    else if (_direction_facing == RIGHT && _motion_type == STANDING)
        return 3;
    else if (_direction_facing == UP && _motion_type == WALKING)
        return 4;
    else if (_direction_facing == DOWN && _motion_type == WALKING)
        return 5;
    else if (_direction_facing == LEFT && _motion_type == WALKING)
        return 6;
    else if (_direction_facing == RIGHT && _motion_type == WALKING)
        return 7;
    else
        return 0;
}

void Player::startMovingUp() {
    if (_move_time <= 0) {
        _direction_facing = UP;
        _move_time = _frames_to_cross_one_tile;
    }
}

void Player::startMovingDown() {
    if (_move_time <= 0) {
        _direction_facing = DOWN;
        _move_time = _frames_to_cross_one_tile;
    }
}

void Player::startMovingLeft() {
    if (_move_time <= 0) {
        _direction_facing = LEFT;
        _move_time = _frames_to_cross_one_tile;
    }
}

void Player::startMovingRight() {
    if (_move_time <= 0) {
        _direction_facing = RIGHT;
        _move_time = _frames_to_cross_one_tile;
    }
}

void Player::stopMoving() {
    _move_time = 0;
}
