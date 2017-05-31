/**
    player.cpp
    Purpose: Manage player logic and sprites

    @author: Zachary Vincze
    @version: 28/05/2017
*/

#include "player.h"
#include "game.h"

namespace {
    const std::string kSpriteFilePath = "res/player.png";

    const float kWalkSpeed = 0.06f;
    const int kPlayerFrame = 0;

    const int kNumWalkFrames = 4;
    const int kNumSidewayWalkFrames = 2;
    const int kWalkFps = 5;
}

Player::Player(Graphics& graphics, int x, int y) {
    mX = x;
    mY = y;
    mVelocityX = 0;
    mVelocityY = 0;
    mSprites.resize(8);

    mDirectionFacing = RIGHT;
    mMotionType = WALKING;

    // Load sprites
    // ----- STATIC SPRITES
    mSprites[0] = new Sprite(graphics, kSpriteFilePath, 0, 0, Game::kTileSize, Game::kTileSize);
    mSprites[1] = new Sprite(graphics, kSpriteFilePath, 0, Game::kTileSize, Game::kTileSize, Game::kTileSize);
    mSprites[2] = new Sprite(graphics, kSpriteFilePath, 0, Game::kTileSize * 2, Game::kTileSize, Game::kTileSize);
    mSprites[3] = new Sprite(graphics, kSpriteFilePath, 0, Game::kTileSize * 3, Game::kTileSize, Game::kTileSize);

    // ----- ANIMATED SPRITES
    mSprites[4] = new AnimatedSprite(graphics, kSpriteFilePath, 0, 0, Game::kTileSize, Game::kTileSize, kWalkFps, kNumWalkFrames);
    mSprites[5] = new AnimatedSprite(graphics, kSpriteFilePath, 0, Game::kTileSize, Game::kTileSize, Game::kTileSize, kWalkFps, kNumWalkFrames);
    mSprites[6] = new AnimatedSprite(graphics, kSpriteFilePath, 0, Game::kTileSize * 2, Game::kTileSize, Game::kTileSize, kWalkFps, kNumSidewayWalkFrames);
    mSprites[7] = new AnimatedSprite(graphics, kSpriteFilePath, 0, Game::kTileSize * 3, Game::kTileSize, Game::kTileSize, kWalkFps, kNumSidewayWalkFrames);
}

void Player::update(int elapsed_time_ms) {
    mSprites[getSpriteID()]->update(elapsed_time_ms);

    mTempX += mVelocityX * elapsed_time_ms;
    mX = round(mTempX);

    mTempY += mVelocityY * elapsed_time_ms;
    mY = round(mTempY);
}

void Player::draw(Graphics& graphics) {
    mSprites[getSpriteID()]->draw(graphics, mX, mY);
}

int Player::getSpriteID() {

    if (mVelocityX != 0 || mVelocityY != 0) {
        mMotionType = WALKING;
    } else {
        mMotionType = STANDING;
    }

    if (mDirectionFacing == UP && mMotionType == STANDING)
        return 0;
    else if (mDirectionFacing == DOWN && mMotionType == STANDING)
        return 1;
    else if (mDirectionFacing == LEFT && mMotionType == STANDING)
        return 2;
    else if (mDirectionFacing == RIGHT && mMotionType == STANDING)
        return 3;
    else if (mDirectionFacing == UP && mMotionType == WALKING)
        return 4;
    else if (mDirectionFacing == DOWN && mMotionType == WALKING)
        return 5;
    else if (mDirectionFacing == LEFT && mMotionType == WALKING)
        return 6;
    else if (mDirectionFacing == RIGHT && mMotionType == WALKING)
        return 7;
    else
        return 0;
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
    mVelocityX = 0;
    mVelocityY = 0;
}

void Player::close() {
    for (std::vector<Sprite*>::iterator i = mSprites.begin(); i != mSprites.end(); i++) {
        delete (*i);
    }
}
