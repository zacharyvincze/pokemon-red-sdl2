/**
    animated_sprite.cpp
    Purpose: Handles the animation of sprites

    @author Zachary Vincze
    @version 21/05/2017
*/

#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& file_path, int source_x, int source_y, int width, int height, int fps, int num_frames) :
    Sprite(graphics, file_path, source_x, source_y, width, height) {
    mFrameTime = fps;
    mNumFrames = num_frames;
    mCurrentFrame = 0;
    mElapsedTime = 0;
}

void AnimatedSprite::update() {
    mElapsedTime += 1;
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
