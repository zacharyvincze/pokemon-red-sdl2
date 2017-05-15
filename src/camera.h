#ifndef CAMERA_H
#define CAMERA_H

#include "map.h"

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

        void update(int elapsed_time_ms);

    private:
        int mCameraPosX;
        int mCameraPosY;
        float mCameraVelocityX;
        float mCameraVelocityY;
};

#endif // CAMERA_H
