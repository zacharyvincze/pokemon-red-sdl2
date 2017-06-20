/**
    player.cpp
    Purpose: Manage player logic and sprites

    @author: Zachary Vincze
    @version: 28/05/2017
*/

#include "player.h"
#include "game.h"

namespace {
    const std::string kSpriteFilePath = "gfx/sprites/red.png";

    const float kWalkSpeed = 0.06f;
    const int kPlayerFrame = 0;

    const int kNumWalkFrames = 4;
    const int kNumSidewayWalkFrames = 2;
    const int kWalkFps = 5;

    bool kIsWalking = false;
    bool kIsAtTarget = true;
}

Player::Player(Graphics& graphics, int x, int y) {
    mX = 0;
    mY = 0;
    mTempX = x;
    mTempY = y;
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

    //mTempX += mVelocityX * elapsed_time_ms;
    //mX = round(mTempX);

    //mTempY += mVelocityY * elapsed_time_ms;
    //mY = round(mTempY);

    // Start tile-based movement updates
    if (kIsWalking == true && kIsAtTarget == false) {
        mX += round(mVelocityX * elapsed_time_ms);
        mY += round(mVelocityY * elapsed_time_ms);
    }

    // Check if centered to tile, if so, stop moving the player
    if (mY % Game::kTileSize == 0 && kIsWalking == true) stopMoving();
}

void Player::draw(Graphics& graphics, SDL_Rect& camera) {
    mSprites[getSpriteID()]->draw(graphics, mX - camera.x, (mY - 4) - camera.y);
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
    if (kIsWalking == false) {
        kIsWalking = true;
        kIsAtTarget = false;
        mVelocityY = -kWalkSpeed;
        mDirectionFacing = UP;
    }
}

void Player::startMovingDown() {
    if (kIsWalking == false) {
        kIsWalking = true;
        kIsAtTarget = false;
        mVelocityY = kWalkSpeed;
        mDirectionFacing = DOWN;
    }
}

void Player::startMovingLeft() {
    if (kIsWalking == false) {
        kIsWalking = true;
        kIsAtTarget = false;
        mVelocityX = -kWalkSpeed;
        mDirectionFacing = LEFT;
    }
}

void Player::startMovingRight() {
    if (kIsWalking == false) {
        kIsWalking = true;
        kIsAtTarget = false;
        mVelocityX = kWalkSpeed;
        mDirectionFacing = RIGHT;
    }
}

void Player::stopMoving() {
    kIsWalking = false;
    kIsAtTarget = true;
    mVelocityX = 0;
    mVelocityY = 0;
}

void Player::close() {
    for (std::vector<Sprite*>::iterator i = mSprites.begin(); i != mSprites.end(); i++) {
        delete (*i);
    }
}
