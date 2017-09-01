#ifndef WINDOW_H
#define WINDOW_H

#include "graphics.h"

#include <SDL2/SDL.h>
#include <vector>

class Window {
    public:
        Window(Graphics& graphics, int x, int y, int w, int h);
        ~Window();
        
        SDL_Rect getWindowRect() { return _window_rect; }
        
        void draw(Graphics& graphics);
    private:
        SDL_Texture* _sprite_sheet;
        std::vector<SDL_Rect> _window_tiles;
        SDL_Rect _window_rect;
};

#endif // WINDOW_H