#ifndef GAME_H
#define GAME_H

#include <boost/scoped_ptr.hpp>
#include "map.h"
#include "tilemap.h"
#include "graphics.h"
#include "sprite.h"
#include "camera.h"
#include "animated_sprite.h"
#include "player.h"
#include "input.h"
#include "text.h"

#include <chrono>

class Game {
    public:
        Game();
        ~Game();

        static int kTileSize;

    private:
        void eventLoop();
        void update();
        void draw(Graphics& graphics);
        void close();

        Camera* camera;
        Tilemap tilemap;
        Map* map;
        AnimatedSprite* animated_sprite;
        Player* player;
        Text* text;
};

#endif // GAME_H
