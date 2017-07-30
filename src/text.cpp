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
}

Text::~Text() {
    SDL_DestroyTexture(mSpriteSheet);
}

void Text::print(Graphics& graphics, int x, int y, const std::string& message) {
    SDL_Rect destinationRectangle;
    destinationRectangle.y = y;

    for (int i = 0; i < message.length(); i++) {
        destinationRectangle.x = x + (i * charWidth);
        mSourceRect.x = getXPos(message.at(i));
        mSourceRect.y = getYPos(message.at(i));
        graphics.render(mSpriteSheet, &mSourceRect, &destinationRectangle);
    }
}

// TODO: I really don't like how this is being done too much.
// There's a lot going on and I don't want to make the game run
// any slower because it is trying to map the right text.
int Text::getXPos(char iChar) {
    if (iChar >= 65 && iChar <= 80) {
        return (iChar - 65) * charWidth;
    }
    
    if (iChar >= 81 && iChar <= 90) {
        return (iChar - 81) * charWidth;
    }
    
    if (iChar >= 97 && iChar <= 112) {
        return (iChar - 97) * charWidth;
    }
    
    if (iChar >= 113 && iChar <= 122) {
        return (iChar - 113) * charWidth;
    }
    
    if (iChar >= 48 && iChar <= 57) {
        return (iChar - 42) * charWidth;
    }
    
    if (iChar == 46) {
        return 8 * charWidth;
    }
    
    return 0;
}

int Text::getYPos(char iChar) {
    if (iChar >= 65 && iChar <= 80) {
        return 0;
    }
    
    if (iChar >= 81 && iChar <= 90) {
        return 1 * charWidth;
    }
    
    if (iChar >= 97 && iChar <= 112) {
        return 2 * charWidth;
    }
    
    if (iChar >= 113 && iChar <= 122) {
        return 3 * charWidth;
    }
    
    if (iChar == 32) {
        return 4 * charWidth;
    }
    
    if (iChar >= 48 && iChar <= 57) {
        return 7 * charWidth;
    }
    
    if (iChar == 46) {
        return 6 * charWidth;
    }
    
    return 0;
}