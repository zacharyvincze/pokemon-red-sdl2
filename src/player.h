#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "animated_sprite.h"

#include <vector>

class Player {
    public:
        Player(Graphics& graphics, int x, int y);

        void draw(Graphics& graphics);
        void update(int elapsed_time_ms, SDL_Rect& camera);

        void startMovingUp();
        void startMovingDown();
        void startMovingLeft();
        void startMovingRight();
        void stopMoving();

        enum MotionType {
            WALKING,
            STANDING
        };

        enum DirectionFacing {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        void close();

        int getX() { return mX; }
        int getY() { return mY; }

    private:
        int getSpriteID();

        DirectionFacing mDirectionFacing;
        MotionType mMotionType;

        int mX, mY;
        float mVelocityX, mVelocityY, mTempX, mTempY;

        std::vector<Sprite*> mSprites;
};

#endif // PLAYER_H
