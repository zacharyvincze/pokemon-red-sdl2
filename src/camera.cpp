/**
    mCameraRect.cpp
    Purpose: Handles the mCameraRect movement

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "camera.h"

#include <cmath>

// Camera constants
namespace {
    // const float kCameraSpeed = 0.06f;   // Camera movement speed
    const int kCameraWidth = 256;       // Viewport width
    const int kCameraHeight = 144;      // Viewport height
    
    const int tileSize = 16;
}

// Initialize the mCameraRect class
Camera::Camera() {
    mCameraRect.x = 0;
    mCameraRect.y = 0;
    mCameraRect.w = kCameraWidth;
    mCameraRect.h = kCameraHeight;
}

void Camera::update(Player& player, Map& map) {

    mCameraRect.x = round(player.getPlayerRect().x - 80);
    mCameraRect.y = round(player.getPlayerRect().y - 60);

    if (mCameraRect.x < 0) {
        mCameraRect.x = 0;
    }
    if (mCameraRect.y < 0) {
        mCameraRect.y = 0;
    }
    if (mCameraRect.x > (map.getWidth() * tileSize) - mCameraRect.w) {
        mCameraRect.x = (map.getWidth() * tileSize) - mCameraRect.w;
    }
    if (mCameraRect.y > (map.getHeight() * tileSize) - mCameraRect.h) {
        mCameraRect.y = (map.getHeight() * tileSize) - mCameraRect.h;
    }
}
