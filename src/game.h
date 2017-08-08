#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "graphics.h"
#include "camera.h"
#include "player.h"
#include "input.h"
#include "text.h"
#include "npc.h"

#include <chrono>
#include <vector>
#include <map>

class Game {
    public:
        Game();
        ~Game();

        static int kTileSize;

    private:
        void eventLoop();
        void update();
        void draw(Graphics& graphics);
        void input();

        // Object pointers
        Camera* oCamera;
        Tileset* oTileset;
        Map* oMap;
        Player* oPlayer;
        Text* oText;
        Graphics* oGraphics;
        Input* oInput;
        
        std::map<std::string, NPC*> oNPC;
        
        SDL_Event event;
};

#endif // GAME_H
