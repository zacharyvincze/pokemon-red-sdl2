/**
    sprite.cpp
    Purpose: Handles sprites in the game

    @author Zachary Vincze
    @version 14/05/2017
*/

#include "sprite.h"

// Initailize the sprite class
Sprite::Sprite() {

}

// Load the sprite
void Sprite::load(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height) {
    mSpriteSheet = graphics.loadImage(filePath);
    mSourceRect.x = sourceX;
    mSourceRect.y = sourceY;
    mSourceRect.w = width;
    mSourceRect.h = height;
}

// Draw the sprite
void Sprite::draw(Graphics& graphics, int x, int y) {
    SDL_Rect destinationRectangle;
    destinationRectangle.x = x;
    destinationRectangle.y = y;
    graphics.render(mSpriteSheet, &mSourceRect, &destinationRectangle); // Render the sprite to the screen
}
