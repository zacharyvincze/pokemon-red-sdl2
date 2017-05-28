#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "sprite.h"
#include "animated_sprite.h"
#include <map>

class Player {
    public:
        Player(Graphics& graphics, int x, int y);

        void update(int elapsed_time_ms);
        void draw(Graphics& graphics);

        void startMovingUp();
        void startMovingDown();
        void startMovingLeft();
        void startMovingRight();
        void stopMoving();

    private:
        enum MotionType {
            FIRST_MOTION_TYPE,
            IDLE = FIRST_MOTION_TYPE,
            WALKING,
            LAST_MOTION_TYPE
        };

        enum DirectionFacing {
            FIRST_DIRECTION_FACING,
            UP = FIRST_DIRECTION_FACING,
            DOWN,
            LEFT,
            RIGHT,
            LAST_DIRECTION_FACING
        };

        struct SpriteState {
            SpriteState(MotionType motion_type = IDLE, DirectionFacing direction_facing = LEFT) :
                motion_type(motion_type),
                direction_facing(direction_facing) {}

                MotionType motion_type;
                DirectionFacing direction_facing;
        };

        friend bool operator<(const SpriteState& a, const SpriteState& b);

        void initializeSprites(Graphics& graphics);
        void initializeSprite(Graphics& graphics, const SpriteState& sprite);
        SpriteState getSpriteState();

        int mX, mY;
        float mVelocityX, mVelocityY;
        DirectionFacing mDirectionFacing;

        std::map<SpriteState, Sprite*> mSprites;

};

#endif // PLAYER_H
