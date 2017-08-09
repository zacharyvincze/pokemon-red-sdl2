#include "text.h"

namespace {
    const int charWidth = 8;
    const int charSpacing = 1;
}

Text::Text(Graphics& graphics, const std::string& file_path) {
    mSpriteSheet = graphics.loadImage(file_path);
    mSourceRect.x = 0;
    mSourceRect.y = 0;
    mSourceRect.w = charWidth;
    mSourceRect.h = charWidth;
    
    std::string character_list = "ABCDEFGHIJKLMNOP";
    
    for (int i = 0; i < character_list.length(); i++) {
        _characters[character_list.at(i)] = {i * charWidth, 0, charWidth, charWidth};
    }
    
    character_list = "QRSTUVWXYZ():;[]";
    
    for (int i = 0; i < character_list.length(); i++) {
        _characters[character_list.at(i)] = {i * charWidth, charWidth, charWidth, charWidth};
    }
    
    character_list = "abcdefghijklmnop";
    
    for (int i = 0; i < character_list.length(); i++) {
        _characters[character_list.at(i)] = {i * charWidth, 2 * charWidth, charWidth, charWidth};
    }
    
    character_list = "qrstuvwxyz";
    
    for (int i = 0; i < character_list.length(); i++) {
        _characters[character_list.at(i)] = {i * charWidth, 3 * charWidth, charWidth, charWidth};
    }
    
    character_list = "$*./,^0123456789";
    
    for (int i = 0; i < character_list.length(); i++) {
        _characters[character_list.at(i)] = {i * charWidth, 7 * charWidth, charWidth, charWidth};
    }
}

Text::~Text() {
    SDL_DestroyTexture(mSpriteSheet);
}

void Text::print(Graphics& graphics, int x, int y, const std::string& message) {
    SDL_Rect destinationRectangle;
    destinationRectangle.y = y;

    for (int i = 0; i < message.length(); i++) {
        destinationRectangle.x = x + (i * charWidth);
        SDL_Rect sourceRect = _characters[message.at(i)];
        graphics.render(mSpriteSheet, &sourceRect, &destinationRectangle);
    }
}
