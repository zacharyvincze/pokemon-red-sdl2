#ifndef SPRITE_H
#define SPRITE_H

#include "graphics.h"

#include <string>
#include <SDL2/SDL.h>

class Sprite {
    public:
        Sprite(Graphics& graphics, const std::string& file_path, int source_x, int source_y, int width, int height);
        virtual void update() {}
        void draw(Graphics& graphics, int x, int y);
        void close();

    protected:
        SDL_Rect mSourceRect;
    private:
        SDL_Texture* mSpriteSheet;


};

#endif // SPRITE_H
