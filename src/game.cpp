/**
    game.cpp
    Purpose: Main class for game logic

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "game.h"
#include "map.h"
#include "input.h"
#include "camera.h"
#include "graphics.h"
#include "constants.h"
#include "text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Game constants
namespace {
    const int kFps = 63;    // 63 frames per second beacuse SDL in inacurate
    const int frameDuration = 16;
    const int maxTimePerFrame = 200;
    
    float fps = 0;
    
    bool running = true;
}

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL
    IMG_Init(IMG_INIT_PNG);
    
    oGraphics = new Graphics();
    oInput = new Input();
    // oTileset = new Tileset(*oGraphics, "gfx/tilesets/pokecenter.png");
    oTileset = new Tileset(*oGraphics, "gfx/tilesets/overworld.png");
    oMap = new Map("src/data/maps/pallet_town.dat", "gfx/tilesets/overworld.tilecol", *oTileset, 40, 36);
    // oMap = new Map("src/data/maps/pokecenter.dat", "gfx/tilesets/pokecenter.tilecol", *oTileset, 28, 16);
    oPlayer = new Player(*oGraphics, 1, 3, "gfx/sprites/red.png");
    oCamera = new Camera();
    oText = new Text(*oGraphics, "gfx/font.png");
    oNPCS.push_back(new NPC(*oGraphics, 2, 4, "gfx/sprites/boy.png", "Why hello there!"));
    oNPCS.push_back(new NPC(*oGraphics, 2, 3, "gfx/sprites/red.png", "Why hello there!"));
    
    eventLoop();                // Run the game's event loop
}

// Quit the SDL subsystems
Game::~Game() {
    delete oPlayer;
    delete oMap;
    delete oCamera;
    delete oText;
    delete oTileset;
    delete oGraphics;
    delete oInput;
    
    for (std::vector<NPC*>::iterator i = oNPCS.begin(); i != oNPCS.end(); i++) {
        delete (*i);
    }
    
    IMG_Quit();
    SDL_Quit();
}

void Game::eventLoop() {
    auto lastUpdateTime = std::chrono::high_resolution_clock::now();

    while(running) {
        const int timeStuff = SDL_GetTicks();
        auto currentTime = std::chrono::high_resolution_clock::now();
        // auto accumulatedTime += std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime);

        input();

        // Update
        // while (accumulatedTime >= frameDuration) {
            // accumulatedTime -= frameDuration;
            update();
        // }
        lastUpdateTime = std::chrono::high_resolution_clock::now();

        // Render
        draw(*oGraphics);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - currentTime);

        // Cap the frame rate
        auto delayDuration = std::chrono::milliseconds(1000) / kFps - elapsedTime;
        if (delayDuration.count() >= 0)
            SDL_Delay(delayDuration.count());

        // Measure frames per second
        const float seconds_per_frame = (SDL_GetTicks() - timeStuff) / 1000.0;
        fps = 1 / seconds_per_frame;
        printf("fps=%f\n", fps);
    }
}

void Game::update() {
    oPlayer->update(*oMap, oNPCS);
    
    for (int i = 0; i < oNPCS.size(); i++) {
        oNPCS[i]->update(*oMap);
    }
    
    oCamera->update(*oPlayer, oMap->getMapRect());   // Update the oCamera's position
}

void Game::draw(Graphics& graphics) {
    graphics.clear();                                                   // Clear the renderer
    oMap->draw(graphics, oCamera->getCameraRect());         // Draw the map
    oPlayer->draw(graphics, oCamera->getCameraRect());
    
    for (int i = 0; i < oNPCS.size(); i++) {
        oNPCS[i]->draw(graphics, oCamera->getCameraRect());
    }
    
    oText->print(graphics, 0, 0, std::to_string(oPlayer->getEntityRect().x));
    oText->print(graphics, 0, 8, std::to_string(oPlayer->getEntityRect().y));
    oText->print(graphics, 0, 16, std::to_string(oCamera->getCameraRect().x));
    oText->print(graphics, 0, 24, std::to_string(oCamera->getCameraRect().y));
    oText->print(graphics, 0, 32, std::to_string(fps));
    oText->print(graphics, 0, 40, std::to_string(oPlayer->getMoveTime()));
    oText->print(graphics, 0, 48, std::to_string(oPlayer->getCurrentTile()));
    
    graphics.present();                                                 // Present the renderer
    printf("PLAYER_X: %i\nPLAYER_Y: %i\nCAMERA_X: %i\nCAMERA_Y: %i\n", oPlayer->getEntityRect().x, oPlayer->getEntityRect().y, oCamera->getCameraRect().x, oCamera->getCameraRect().y);
    printf("PLAYER_X_CAMERA: %i\nPLAYER_Y_CAMERA: %i\n\n", oPlayer->getEntityRect().x - oCamera->getCameraRect().x, oPlayer->getEntityRect().y - oCamera->getCameraRect().y);
}

void Game::input() {
    // Get keydown and keyup events for the input object
    while(SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (!event.key.repeat)
                    oInput->keyDownEvent(event);
                break;
            case SDL_KEYUP:
                oInput->keyUpEvent(event);
                break;
            default:
                break;
        }
    }

    // Different inputs
    // If user requests a quit (Either using ESCAPE or Q)
    if (oInput->wasKeyPressed(SDL_SCANCODE_ESCAPE) || oInput->wasKeyPressed(SDL_SCANCODE_Q))
        running = false;

    if (oInput->wasKeyHeld(SDL_SCANCODE_UP)) {
        oPlayer->move(0);
    }
    if (oInput->wasKeyHeld(SDL_SCANCODE_DOWN)) {
        oPlayer->move(1);
    }
    if (oInput->wasKeyHeld(SDL_SCANCODE_LEFT)) {
        oPlayer->move(2);
    }
    if (oInput->wasKeyHeld(SDL_SCANCODE_RIGHT)) {
        oPlayer->move(3);
    }
}
