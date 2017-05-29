#ifndef CAMERA_H
#define CAMERA_H

#include "map.h"
#include "player.h"

#include <chrono>

class Camera {
    public:
        Camera();

        void startMovingRight();
        void startMovingLeft();
        void startMovingUp();
        void startMovingDown();

        void stopMoving();

        int getX() { return mCameraPosX; }
        int getY() { return mCameraPosY; }

        void setY(int y) { mCameraPosY = y; }
        void setX(int x) { mCameraPosX = x; }

        void update(int elapsed_time_ms, Player& player, Map& map);

    private:
        int mCameraPosX;
        int mCameraPosY;
        float mCameraVelocityX;
        float mCameraVelocityY;
        float mTempX;
        float mTempY;
};

#endif // CAMERA_H
