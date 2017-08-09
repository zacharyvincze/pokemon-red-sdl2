#ifndef TEXT_H
#define TEXT_H

#include "graphics.h"
#include <SDL2/SDL.h>

#include <string>
#include <map>

class Text {
    public:
        Text(Graphics& graphics, const std::string& file_path);
        ~Text();

        void print(Graphics& graphics, int x, int y, const std::string& message);

    protected:
        SDL_Rect mSourceRect;

    private:    
        std::map<char, SDL_Rect> _characters;

        SDL_Texture* mSpriteSheet;
};

#endif // TEXT_H
