#ifndef GAME_H
#define GAME_H

#include <boost/scoped_ptr.hpp>
#include "map.h"
#include "tilemap.h"
#include "graphics.h"
#include "sprite.h"
#include "camera.h"
#include "animated_sprite.h"

#include <chrono>

class Game {
    public:
        Game();
        ~Game();

        static int kTileSize;

    private:
        void eventLoop();
        void update(int elapsed_time_ms);
        void draw(Graphics& graphics);

        Tilemap tilemap;
        Map map;
        AnimatedSprite animated_sprite;
        Sprite sprite;
        Camera camera;
};

#endif // GAME_H
