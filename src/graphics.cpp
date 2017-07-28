/**
    graphics.cpp
    Purpose: Handles everything to do with graphics

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "graphics.h"
#include <SDL2/SDL_image.h>

// Graphic constants
namespace {
    const int kScreenWidth = 256;   // Window width
    const int kScreenHeight = 144;  // Window height

    const int kRendererWidth = 256;     // Renderer width
    const int kRendererHeight = 144;    // Renderer height

    const int kRendererRed = 0;     // Renderer draw color (red)
    const int kRendererGreen = 0;   // Renderer draw color (green)
    const int kRendererBlue = 0;    // Renderer draw color (blue)
    const int kRendererAlpha = 1;   // Renderer transparency
}

// Initialize SDL and tweak some settings
Graphics::Graphics() {
    mWindow = SDL_CreateWindow("Pokemon Red", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(mRenderer, kRendererWidth, kRendererHeight);   // Set renderer height and width
    SDL_ShowCursor(SDL_DISABLE);                                            // Prevent the cursor from being shown
}

// Clean up textures
Graphics::~Graphics() {
    // Remove every texture used
    for (SpriteMap::iterator iter = mSpriteSheets.begin(); iter != mSpriteSheets.end(); ++iter) {
        SDL_DestroyTexture(iter->second);
    }

    SDL_DestroyWindow(mWindow);     // Destroy the window
    SDL_DestroyRenderer(mRenderer); // Destroy the renderer
}

// Load images for spritesheets
Graphics::SurfaceID Graphics::loadImage(const std::string& filePath) {
    // Check if this spritesheet is being used already
    if (mSpriteSheets.count(filePath) == 0) {
        SDL_Surface* image = IMG_Load(filePath.c_str());                            // Load image to a surface
        mSpriteSheets[filePath] = SDL_CreateTextureFromSurface(mRenderer, image);   // Create texture from the surface
        SDL_FreeSurface(image);                                                     // Free the surface
    }

    return mSpriteSheets[filePath]; // Return the spritesheet
}

// Render textures to the buffer
void Graphics::render(SurfaceID source, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle) {
    // Add clipping if specified
    if (sourceRectangle) {
        destinationRectangle->w = sourceRectangle->w;   // Set destination rectangle width to the source rectangle's width
        destinationRectangle->h = sourceRectangle->h;   // Set destination rectangle height to the source rectangle's height
    }

    SDL_RenderCopy(mRenderer, source, sourceRectangle, destinationRectangle);   // Copy the final texture to the buffer
}

// Clear textures from the buffer
void Graphics::clear() {
    SDL_SetRenderDrawColor(mRenderer, kRendererRed, kRendererGreen, kRendererBlue, kRendererAlpha); // Set the renderer's draw color
    SDL_RenderClear(mRenderer);                                                                     // Clear the renderer
}

// Present textures from the buffer to the screen
void Graphics::present() {
    SDL_RenderPresent(mRenderer);   // Present the renderer
}
