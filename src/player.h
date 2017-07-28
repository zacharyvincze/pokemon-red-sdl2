#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "animated_sprite.h"
#include "map.h"

#include <vector>

class Player {
    public:
        Player(Graphics& graphics, int x, int y, const std::string& file_path);
        ~Player();

        void draw(Graphics& graphics, SDL_Rect& camera);
        void draw(Graphics& graphics);
        void update(SDL_Rect& mapRect);

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

        SDL_Rect getPlayerRect() { return mPlayerRect; }

    private:
        int getSpriteID();

        DirectionFacing mDirectionFacing;
        MotionType mMotionType;

        int mX, mY, mTargetX, mTargetY;
        float mVelocityX, mVelocityY, mTempX, mTempY;
        bool isWalking, atTarget;

        std::vector<Sprite*> mSprites;
        
        SDL_Rect mPlayerRect;
};

#endif // PLAYER_H
