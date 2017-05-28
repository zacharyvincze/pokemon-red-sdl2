/**
    player.cpp
    Purpose: Controlling player sprites and logic

    @author Zachary Vincze
    @version: 28/05/2017
*/

#include "player.h"
#include "game.h"

namespace {
    // Walk Motion
    const float kWalkSpeed = 0.03;

    // Sprites
    const std::string kSpriteFilePath = "res/player.png";

    // Sprite Frames
    const int kWalkFrame = 0;
    const int kStandFrame = 0;

    // Walk animation
    const int kNumWalkFrames = 4;
    const int kWalkFps = 5;

    // Character
    const int kCharacterFrame = 0;
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b) {
    if (a.motion_type != b.motion_type) {
        return a.motion_type < b.motion_type;
    }
    if (a.direction_facing != b.direction_facing) {
        return a.direction_facing < b.direction_facing;
    }
    return false;
}

Player::Player(Graphics& graphics, int x, int y) {
    mX = x;
    mY = y;
    mVelocityX = 0;
    mVelocityY = 0;
    mDirectionFacing = LEFT;
    initializeSprites(graphics);
}

void Player::update(int elapsed_time_ms) {
    mSprites[getSpriteState()]->update(elapsed_time_ms);

    mX += round(mVelocityX * elapsed_time_ms);
    mY += round(mVelocityY * elapsed_time_ms);
}

void Player::draw(Graphics& graphics) {
    mSprites[SpriteState(WALKING, LEFT)]->draw(graphics, mX, mY);
}

void Player::startMovingUp() {
    mVelocityY = -kWalkSpeed;
    mDirectionFacing = UP;
}

void Player::startMovingDown() {
    mVelocityY = kWalkSpeed;
    mDirectionFacing = DOWN;
}

void Player::startMovingLeft() {
    mVelocityX = -kWalkSpeed;
    mDirectionFacing = LEFT;
}

void Player::startMovingRight() {
    mVelocityX = kWalkSpeed;
    mDirectionFacing = RIGHT;
}

void Player::stopMoving() {
    mVelocityY = 0.0f;
    mVelocityX = 0.0f;
}

void Player::initializeSprites(Graphics& graphics) {
    for (MotionType motion_type = FIRST_MOTION_TYPE; motion_type < LAST_MOTION_TYPE; motion_type = static_cast<MotionType>(motion_type+1)) {
        for (DirectionFacing direction_facing = FIRST_DIRECTION_FACING; direction_facing < LAST_DIRECTION_FACING; direction_facing = static_cast<DirectionFacing>(direction_facing+1)) {
            initializeSprite(graphics, SpriteState(motion_type, direction_facing));
        }
    }
}

void Player::initializeSprite(Graphics& graphics, const SpriteState& sprite_state) {
    int source_y = sprite_state.direction_facing == UP ? kCharacterFrame*Game::kTileSize : (1 + kCharacterFrame)*Game::kTileSize;

    int source_x;
    switch (sprite_state.motion_type) {
        case WALKING:
            source_x = kWalkFrame * Game::kTileSize;
            break;
        case IDLE:
            source_x = kStandFrame * Game::kTileSize;
            break;
        case LAST_MOTION_TYPE:
            break;
    }

    if (sprite_state.motion_type == WALKING) {
        // Create an animated sprite
        mSprites[sprite_state] = new AnimatedSprite(graphics, kSpriteFilePath, source_x, source_y, Game::kTileSize, Game::kTileSize, kWalkFps, kNumWalkFrames);
    } else {
        mSprites[sprite_state] = new Sprite(graphics, kSpriteFilePath, source_x, source_y, Game::kTileSize, Game::kTileSize);
    }
}

Player::SpriteState Player::getSpriteState() {
    MotionType motion;
    if (mVelocityX != 0 || mVelocityY != 0) {
        motion = WALKING;
    }

    return SpriteState(motion, mDirectionFacing);
}
