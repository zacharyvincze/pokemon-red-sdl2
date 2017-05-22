#ifndef SPRITE_H
#define SPRITE_H

#include "graphics.h"

#include <string>
#include <SDL2/SDL.h>

class Sprite {
    public:
        Sprite();
        void load(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height);
        virtual void update(int) {}
        void draw(Graphics& graphics, int x, int y);

    protected:
        SDL_Rect mSourceRect;
    private:
        SDL_Texture* mSpriteSheet;


};

#endif // SPRITE_H
