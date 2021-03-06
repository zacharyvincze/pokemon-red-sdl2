#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"

// Extended sprite class
class AnimatedSprite : public Sprite {
    public:
        AnimatedSprite(Graphics& graphics, const std::string& file_path, int source_x, int source_y, int width, int height, int fps, int num_frames);

        void update();
        void resetTimer() { mCurrentFrame = 0; mElapsedTime = 0; mSourceRect.x = 0;}

    private:
        int mFrameTime;
        int mNumFrames;
        int mCurrentFrame;
        int mElapsedTime;
};

#endif // ANIMATED_SPRITE_H
