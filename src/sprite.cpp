#include "sprite.h"

// Initailize the sprite class
Sprite::Sprite(Graphics& graphics, const std::string& file_path, int source_x, int source_y, int width, int height) {
    mSpriteSheet = graphics.loadImage(file_path);
    mSourceRect.x = source_x;
    mSourceRect.y = source_y;
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

void Sprite::close() {
    SDL_DestroyTexture(mSpriteSheet);
}
