#ifndef CAMERA_H
#define CAMERA_H

#include "map.h"
#include "player.h"

#include <chrono>

class Camera {
    public:
        Camera();

        SDL_Rect getCamera() { return camera; }

        void update(int elapsed_time_ms, Player& player, Map& map);

    private:
        SDL_Rect camera;
};

#endif // CAMERA_H
