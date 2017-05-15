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
    const float kCameraSpeed = 0.1f;   // Camera movement speed
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

void Camera::update(int elapsed_time_ms) {
    mCameraPosX += round(mCameraVelocityX * elapsed_time_ms);   // Update the camera's X position
    mCameraPosY += round(mCameraVelocityY * elapsed_time_ms);   // Update the camera's Y position

    // TODO: Add map collision detection
}
