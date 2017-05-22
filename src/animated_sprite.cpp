/**
    animated_sprite.cpp
    Purpose: Handles the animation of sprites

    @author Zachary Vincze
    @version 21/05/2017
*/

#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite() {
    mFrameTime = 0;
    mNumFrames = 0;
    mCurrentFrame = 0;
    mElapsedTime = 0;
}

void AnimatedSprite::load(Graphics& graphics, const std::string& file_path, int source_x, int source_y, int width, int height, int fps, int num_frames) {
    Sprite::load(graphics, file_path, source_x, source_y, width, height);
    mFrameTime = (1000 / fps);
    mNumFrames = num_frames;
    mCurrentFrame = 0;
    mElapsedTime = 0;
}

void AnimatedSprite::update(int elapsed_time_ms) {
    mElapsedTime += elapsed_time_ms;
    if (mElapsedTime > mFrameTime) {
        ++mCurrentFrame;
        mElapsedTime = 0;
        if (mCurrentFrame < mNumFrames) {
            mSourceRect.x += 16;
        } else {
            mSourceRect.x -= 16 * (mNumFrames - 1);
            mCurrentFrame = 0;
        }
    }
}
