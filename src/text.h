#ifndef TEXT_H
#define TEXT_H

#include "graphics.h"
#include <SDL2/SDL.h>

#include <string>

class Text {
    public:
        Text(Graphics& graphics, const std::string& file_path);
        ~Text();

        void draw(Graphics& graphics, int x, int y, const std::string& message);

    protected:
        SDL_Rect mSourceRect;

    private:
        int getXPos(char iChar);
        int getYPos(char iChar);

        SDL_Texture* mSpriteSheet;
};

#endif // TEXT_H
