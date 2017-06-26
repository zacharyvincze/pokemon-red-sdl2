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
    // const float kCameraSpeed = 0.06f;   // Camera movement speed
    const int kCameraWidth = 160;       // Viewport width
    const int kCameraHeight = 144;      // Viewport height
}

// Initialize the camera class
Camera::Camera() {
    camera.x = 0;
    camera.y = 0;
    camera.w = kCameraWidth;
    camera.h = kCameraHeight;
}

void Camera::update(Player& player, Map& map) {

    camera.x = round(player.getX() - 80);
    camera.y = round(player.getY() - 60);

    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > (map.getWidth() * 16) - camera.w) {
        camera.x = (map.getWidth() * 16) - camera.w;
    }
    if (camera.y > (map.getHeight() * 16) - camera.h) {
        camera.y = (map.getHeight() * 16) - camera.h;
    }
}
