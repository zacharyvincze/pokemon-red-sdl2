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
#include "constants.cpp"
#include "text.h"

#include "data/maps/pallet_town.cpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Game constants
namespace {
    const float frameDuration = 16.67f;
    const int maxTimePerFrame = 200;
    int accumulatedTime = 0;

    int lastUpdateTime = 0;
    int currentTime = 0;
    
    float fps = 0;
    
    bool running = true;
}

int Game::kTileSize = 16;

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL
    IMG_Init(IMG_INIT_PNG);
    
    oGraphics = new Graphics();
    oInput = new Input();
    oMap = new Map();
    oPlayer = new Player(*oGraphics, 1, 2, "gfx/sprites/red.png");
    oCamera = new Camera();
    oText = new Text(*oGraphics, "gfx/font.png");
    oTileset = new Tileset(*oGraphics, "gfx/tilesets/tileset.png");
    oNPCS.push_back(new NPC(*oGraphics, 2, 2, "gfx/sprites/boy.png", "Why hello there!"));
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
    
    for (int i = 0; i < oNPCS.size(); i++) {
        delete oNPCS[i];
    }
    
    IMG_Quit();
    SDL_Quit();
}

void Game::eventLoop() {
    oMap->load(pallet_town::MAP_TILES, pallet_town::MAP_WIDTH, pallet_town::MAP_HEIGHT);

    lastUpdateTime = SDL_GetTicks();

    while(running) {
        currentTime = SDL_GetTicks();
        accumulatedTime += (currentTime - lastUpdateTime);

        // if (accumulatedTime > maxTimePerFrame) accumulatedTime = maxTimePerFrame;

        input();

        // Update
        //while (accumulatedTime >= frameDuration) {
            //accumulatedTime -= frameDuration;
            update();
        //}
        lastUpdateTime = SDL_GetTicks();

        // Render
        draw(*oGraphics);

        // Cap the frame rate
        if (SDL_GetTicks() - currentTime < frameDuration) {
            SDL_Delay(frameDuration - (SDL_GetTicks() - currentTime));
        }

        // Measure frames per second
        const float seconds_per_frame = (SDL_GetTicks() - currentTime) / 1000.0;
        fps = 1 / seconds_per_frame;
        printf("fps=%f\n", fps);
    }
}

void Game::update() {
    oPlayer->update(oMap->getMapRect());
    
    oNPCS[0]->startMovingDown();
    
    for (int i = 0; i < oNPCS.size(); i++) {
        oNPCS[i]->update(oMap->getMapRect());
    }
    
    oCamera->update(*oPlayer, oMap->getMapRect());   // Update the oCamera's position
}

void Game::draw(Graphics& graphics) {
    graphics.clear();                                                   // Clear the renderer
    oMap->draw(graphics, *oTileset, oCamera->getCameraRect());         // Draw the map
    oPlayer->draw(graphics, oCamera->getCameraRect());
    
    for (int i = 0; i < oNPCS.size(); i++) {
        oNPCS[i]->draw(graphics, oCamera->getCameraRect());
    }
    
    oText->print(graphics, 0, 0, std::to_string(oPlayer->getPlayerRect().x));
    oText->print(graphics, 0, 8, std::to_string(oPlayer->getPlayerRect().y));
    oText->print(graphics, 0, 16, std::to_string(oCamera->getCameraRect().x));
    oText->print(graphics, 0, 24, std::to_string(oCamera->getCameraRect().y));
    oText->print(graphics, 0, 32, std::to_string(fps));
    graphics.present();                                                 // Present the renderer
    printf("PLAYER_X: %i\nPLAYER_Y: %i\nCAMERA_X: %i\nCAMERA_Y: %i\n", oPlayer->getPlayerRect().x, oPlayer->getPlayerRect().y, oCamera->getCameraRect().x, oCamera->getCameraRect().y);
    printf("PLAYER_X_CAMERA: %i\nPLAYER_Y_CAMERA: %i\n\n", oPlayer->getPlayerRect().x - oCamera->getCameraRect().x, oPlayer->getPlayerRect().y - oCamera->getCameraRect().y);
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
        oPlayer->startMovingUp();
    }
    if (oInput->wasKeyHeld(SDL_SCANCODE_DOWN)) {
        oPlayer->startMovingDown();
    }
    if (oInput->wasKeyHeld(SDL_SCANCODE_LEFT)) {
        oPlayer->startMovingLeft();
    }
    if (oInput->wasKeyHeld(SDL_SCANCODE_RIGHT)) {
        oPlayer->startMovingRight();
    }
}
