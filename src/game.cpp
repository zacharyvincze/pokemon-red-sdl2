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

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// TODO: Fix include statements, only include what is necessary

// Game constants
namespace {
    const int kFps = 60;
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
    // animated_sprite = new AnimatedSprite(graphics, "res/player.png", 0, Game::kTileSize * 3, Game::kTileSize, Game::kTileSize, 5, 2);
    player = new Player(graphics, Game::kTileSize * 1, Game::kTileSize * 2);
    camera = new Camera();

    tilemap.load(graphics, "gfx/tilesets/overworld.png");
    map->load(Map::PALLET_TOWN);

    SDL_Event event;    // SDL event handler

    bool running = true;                    // Loop flag
    int last_update_time = SDL_GetTicks();  // Initialize update timer
    int frame_time;

    while(running) {
        frame_time = SDL_GetTicks();   // Get start time

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
        const int current_time_ms = SDL_GetTicks(); // Get the current time
        update(current_time_ms - last_update_time); // Pass the elapsed time to the update function
        last_update_time = current_time_ms;         // Update the update timer

        // Render
        draw(graphics);

        // Cap the frame rate
        if (SDL_GetTicks() - frame_time < MIN_FRAME_TIME) {
            SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks() - frame_time));               // Delay the program to cap the frame rate
        }

        // Measure frames per second
        /*const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
        const float fps = 1 / seconds_per_frame;
        printf("fps=%f\n", fps);*/
    }
}

void Game::update(int elapsed_time_ms) {
    player->update(elapsed_time_ms);
    camera->update(elapsed_time_ms, *player, *map);     // Update the camera's position
    // animated_sprite->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
    graphics.clear();                                                   // Clear the renderer
    map->draw(graphics, tilemap, camera->getCamera());          // Draw the map
    // animated_sprite->draw(graphics, Game::kTileSize * 1, Game::kTileSize * 2);
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
