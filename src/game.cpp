/**
    game.cpp
    Purpose: Main class for game logic

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "game.h"
#include "tilemap.h"
#include "map.h"
#include "input.h"
#include "camera.h"
#include "graphics.h"
#include "constants.cpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Game constants
namespace {
    const int fps = 60;
    const int frameDuration = 16;
    const int maxTimePerFrame = 200;
    int accumulatedTime = 0;

    int lastUpdateTime = 0;
    int currentTime = 0;
}

int Game::kTileSize = 16;

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL
    eventLoop();                // Run the game's event loop
}

// Quit the SDL subsystems
Game::~Game() {
    close();
}

void Game::eventLoop() {
    Graphics graphics;
    Input input;        // Object for handling inputs
    map = new Map();
    player = new Player(graphics, 1, 2);
    camera = new Camera();

    tilemap.load(graphics, "gfx/tilesets/overworld.png");
    map->load(MapConst::PALLET_TOWN);

    SDL_Event event;    // SDL event handler

    bool running = true;                    // Loop flag
    lastUpdateTime = SDL_GetTicks();

    while(running) {
        currentTime = SDL_GetTicks();
        accumulatedTime += (currentTime - lastUpdateTime);

        if (accumulatedTime > maxTimePerFrame) accumulatedTime = maxTimePerFrame;

        // Get keydown and keyup events for the input object
        while(SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (!event.key.repeat)
                        input.keyDownEvent(event);
                    break;
                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;
                default:
                    break;
            }
        }

        // Different inputs
        // If user requests a quit (Either using ESCAPE or Q)
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) || input.wasKeyPressed(SDL_SCANCODE_Q))
            running = false;

        // Player movement
        if (input.wasKeyHeld(SDL_SCANCODE_LEFT) && input.wasKeyHeld(SDL_SCANCODE_RIGHT)) {
            // player->stopMoving();
        }
        else if (input.wasKeyHeld(SDL_SCANCODE_UP) && input.wasKeyHeld(SDL_SCANCODE_DOWN)) {
            // player->stopMoving();
        }
        else if (input.wasKeyHeld(SDL_SCANCODE_UP)) {
            player->startMovingUp();
        }
        else if (input.wasKeyHeld(SDL_SCANCODE_DOWN)) {
            player->startMovingDown();
        }
        else if (input.wasKeyHeld(SDL_SCANCODE_LEFT)) {
            player->startMovingLeft();
        }
        else if (input.wasKeyHeld(SDL_SCANCODE_RIGHT)) {
            player->startMovingRight();
        }
        else {
            // player->stopMoving();
        }

        // Update
        while (accumulatedTime >= frameDuration) {
            accumulatedTime -= frameDuration;
            update();
        }
        lastUpdateTime = SDL_GetTicks();

        // Render
        draw(graphics);

        // Cap the frame rate
        if (SDL_GetTicks() - currentTime < frameDuration) {
            SDL_Delay(frameDuration - (SDL_GetTicks() - currentTime));
        }

        // Measure frames per second
        /*const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
        const float fps = 1 / seconds_per_frame;
        printf("fps=%f\n", fps);*/
    }
}

void Game::update() {
    player->update();
    camera->update(*player, *map);     // Update the camera's position
    // animated_sprite->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
    graphics.clear();                                                   // Clear the renderer
    map->draw(graphics, tilemap, camera->getCamera());          // Draw the map
    player->draw(graphics, camera->getCamera());
    graphics.present();                                                 // Present the renderer
    printf("PLAYER_X: %i\nPLAYER_Y: %i\nCAMERA_X: %i\nCAMERA_Y: %i\n", player->getX(), player->getY(), camera->getCamera().x, camera->getCamera().y);
    printf("PLAYER_X_CAMERA: %i\nPLAYER_Y_CAMERA: %i\n\n", player->getX() - camera->getCamera().x, player->getY() - camera->getCamera().y);
}

void Game::close() {
    tilemap.close();
    // animated_sprite->close();
    player->close();
    delete animated_sprite;
    delete player;
    delete map;
    delete camera;
    IMG_Quit();
    SDL_Quit();
}
