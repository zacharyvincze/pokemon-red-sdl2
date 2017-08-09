#include "camera.h"
#include "constants.h"

#include <cmath>

// Camera constants
namespace {
    // const float kCameraSpeed = 0.06f;   // Camera movement speed
    const short kCameraWidth = 256;       // Viewport width
    const short kCameraHeight = 144;      // Viewport height
}

// Initialize the mCameraRect class
Camera::Camera() {
    mCameraRect.x = 0;
    mCameraRect.y = 0;
    mCameraRect.w = kCameraWidth;
    mCameraRect.h = kCameraHeight;
}

void Camera::update(Player& player, SDL_Rect& mapRect) {

    mCameraRect.x = round(player.getEntityRect().x - 80);
    mCameraRect.y = round(player.getEntityRect().y - 60);

    if (!(mCameraRect.w > (mapRect.w * Constants::TILE_SIZE)) || !(mCameraRect.h > (mapRect.h * Constants::TILE_SIZE))) {
        if (mCameraRect.x < (mapRect.x * Constants::TILE_SIZE)) {
            mCameraRect.x = (mapRect.x * Constants::TILE_SIZE);
        }
        if (mCameraRect.y < (mapRect.y * Constants::TILE_SIZE)) {
            mCameraRect.y = (mapRect.y * Constants::TILE_SIZE);
        }
        if (mCameraRect.x > (mapRect.w * Constants::TILE_SIZE) - mCameraRect.w) {
            mCameraRect.x = (mapRect.w *  Constants::TILE_SIZE) - mCameraRect.w;
        }
        if (mCameraRect.y > (mapRect.h *  Constants::TILE_SIZE) - mCameraRect.h) {
            mCameraRect.y = (mapRect.h *  Constants::TILE_SIZE) - mCameraRect.h;
        }
    }
}
