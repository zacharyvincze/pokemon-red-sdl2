#include "game.h"
#include "constants.h"
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Game constants
namespace {
    const int gameFPS = 60;
    const int frameDuration = 16;
    const int maxTimePerFrame = 200;
    
    auto time_init = std::chrono::high_resolution_clock::now();
    
    float fps = 0;
    
    bool running = true;
}

double Game::getTicks() {
    auto time_current = std::chrono::high_resolution_clock::now();
    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_current - time_init);
    double delta = time_diff.count();
    return delta;
}

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL
    IMG_Init(IMG_INIT_PNG);
    
    oGraphics = new Graphics();
    oInput = new Input();
    // oTileset = new Tileset(*oGraphics, "gfx/tilesets/pokecenter.png", "gfx/tilesets/pokecenter.tilecol");
    oTileset = new Tileset(*oGraphics, "gfx/tilesets/overworld.png", "gfx/tilesets/overworld.tilecol");
    oMap = new Map("maps/route_1.map", *oTileset);
    // oMap = new Map("maps/viridian_city.map", *oTileset);
    // oMap = new Map("maps/pallet_town.map", *oTileset);
    // oMap = new Map("maps/pokecenter.map", *oTileset);
    // oMap = new Map("maps/pokemart.map", *oTileset);
    oPlayer = new Player(*oGraphics, 4, 25, "gfx/sprites/red.png");
    oCamera = new Camera();
    oText = new Text(*oGraphics, "gfx/font.png");
    // oNPC["BOY"] = new NPC(*oGraphics, 21, 30, "gfx/sprites/boy.png", "What's up?");
    
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
    
    for (std::map<std::string, NPC*>::iterator i = oNPC.begin(); i != oNPC.end(); i++) {
        delete (i->second);
    }
    
    IMG_Quit();
    SDL_Quit();
}

void Game::eventLoop() {
    while(running) {
        double time_start = getTicks();

        input();
        update();
        
        auto elapsed_time = getTicks() - time_start;
        
        // Cap the frame rate
        while (elapsed_time < frameDuration) {
            elapsed_time = getTicks() - time_start;
        }
        
        // Render
        draw(*oGraphics);

        // Measure frames per second
        fps = 1 / ((getTicks() - time_start) / 1000);
        printf("fps=%f\n", fps);
    }
}

void Game::update() {
    oPlayer->update(*oMap, oNPC);
    
    for (std::map<std::string, NPC*>::iterator i = oNPC.begin(); i != oNPC.end(); i++) {
        i->second->update(*oMap);
    }
    
    oCamera->update(*oPlayer, oMap->getMapRect());   // Update the oCamera's position
}

void Game::draw(Graphics& graphics) {
    graphics.clear();                                                   // Clear the renderer
    oMap->draw(graphics, oCamera->getCameraRect());         // Draw the map
    oPlayer->draw(graphics, oCamera->getCameraRect());
    
    for (std::map<std::string, NPC*>::iterator i = oNPC.begin(); i != oNPC.end(); i++) {
        i->second->draw(graphics, oCamera->getCameraRect());
    }
    
    oText->print(graphics, 0, 0, std::to_string(oPlayer->getEntityRect().x));
    oText->print(graphics, 0, 8, std::to_string(oPlayer->getEntityRect().y));
    oText->print(graphics, 0, 16, std::to_string(oCamera->getCameraRect().x));
    oText->print(graphics, 0, 24, std::to_string(oCamera->getCameraRect().y));
    oText->print(graphics, 0, 32, std::to_string(fps));
    oText->print(graphics, 0, 40, std::to_string(oPlayer->getMoveTime()));
    
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
