/**
    camera.cpp
    Purpose: Handles the camera movement

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "camera.h"

#include <cmath>

// Camera constants
namespace {
    const float kCameraSpeed = 0.03f;   // Camera movement speed
    const int kCameraWidth = 160;       // Viewport width
    const int kCameraHeight = 144;      // Viewport height
}

// Initialize the camera class
Camera::Camera() {
    mCameraPosX = 0;
    mCameraPosY = 0;
    mCameraVelocityY = 0;
    mCameraVelocityX = 0;
}

void Camera::startMovingRight() {
    mCameraVelocityX = kCameraSpeed;    // VelocityX = positive movement speed
}

void Camera::startMovingLeft() {
    mCameraVelocityX = -kCameraSpeed;   // VelocityX = negative movement speed
}

void Camera::startMovingUp() {
    mCameraVelocityY = -kCameraSpeed;   // VelocityY = negative movement speed
}

void Camera::startMovingDown() {
    mCameraVelocityY = kCameraSpeed;    // VelocityY = positive movement speed
}

void Camera::stopMoving() {
    mCameraVelocityX = 0;   // Reset the camera's X velocity
    mCameraVelocityY = 0;   // Reset the camera's Y velocity
}

void Camera::update(int elapsed_time_ms, Player& player, Map& map) {
    if (mCameraPosX > 0 || mCameraPosX < map.getWidth() * 16) {
        mTempX += mCameraVelocityX * elapsed_time_ms;
        mCameraPosX = round(mTempX);
    }

    if (mCameraPosY + kCameraHeight - 1 < map.getHeight() * 16) {
        mTempY += mCameraVelocityY * elapsed_time_ms;
        mCameraPosY = round(mTempY);
    } else {
        mCameraPosY -= 1;
    }

    printf("%i\n%i\n\n", map.getHeight() * 16, mCameraPosY + kCameraHeight);
}
