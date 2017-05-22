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
    IMG_Quit();
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;  // Object for handling graphics
    Input input;        // Object for handling inputs

    // Load sprites
    tilemap.load(graphics, "res/tileset.png");                                          // Load the tilemap
    animated_sprite.load(graphics, "res/sprites.png", 0, 0, Game::kTileSize, Game::kTileSize, 5, 4);   // Load the player sprite
    map.load(Map::PALETTE_TOWN);                                                        // Load the map

    SDL_Event event;    // SDL event handler

    bool running = true;                    // Loop flag
    int last_update_time = SDL_GetTicks();  // Initialize update timer

    while(running) {
        const int start_time_ms = SDL_GetTicks();   // Get start time

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

        // Temporary camera movement TODO: Needs to be fixed, this is terribly broken
        if (input.wasKeyHeld(SDL_SCANCODE_DOWN))
            camera.startMovingDown();
        else if (input.wasKeyHeld(SDL_SCANCODE_UP))
            camera.startMovingUp();
        else if (input.wasKeyHeld(SDL_SCANCODE_LEFT))
            camera.startMovingLeft();
        else if (input.wasKeyHeld(SDL_SCANCODE_RIGHT))
            camera.startMovingRight();
        else
            camera.stopMoving();

        // Update
        const int current_time_ms = SDL_GetTicks(); // Get the current time
        update(current_time_ms - last_update_time); // Pass the elapsed time to the update function
        last_update_time = current_time_ms;         // Update the update timer

        // Cap the frame rate
        const int elapsed_time_ms = start_time_ms - SDL_GetTicks(); // Get the elapsed time
        if (elapsed_time_ms < (1000 / kFps)) {
            SDL_Delay(1000 / kFps - elapsed_time_ms);               // Delay the program to cap the frame rate
        }

        // Render
        draw(graphics);

        // Measure frames per second
        /*const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
        const float fps = 1 / seconds_per_frame;
        printf("fps=%f\n", fps);*/
    }
}

void Game::update(int elapsed_time_ms) {
    camera.update(elapsed_time_ms);     // Update the camera's position
    animated_sprite.update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
    graphics.clear();                                                   // Clear the renderer
    map.draw(graphics, tilemap, camera.getX(), camera.getY());          // Draw the map
    animated_sprite.draw(graphics, 1 * Game::kTileSize, 2 * Game::kTileSize);    // Draw the player sprite
    graphics.present();                                                 // Present the renderer
}
