#include "window.h"
#include "constants.h"

Window::Window(Graphics& graphics, int x, int y, int w, int h) {
    _window_rect.x = x;
    _window_rect.y = y;
    _window_rect.w = w;
    _window_rect.h = h;
    
    _sprite_sheet = graphics.loadImage("gfx/window.png");
    
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            _window_tiles.push_back({x * Constants::TILE_SIZE, y * Constants::TILE_SIZE, Constants::TILE_SIZE, Constants::TILE_SIZE});
        }
    }
}

Window::~Window() {
    SDL_DestroyTexture(_sprite_sheet);
}

void Window::draw(Graphics& graphics) {
    SDL_Rect destination_rectangle;
    destination_rectangle.x = _window_rect.x * Constants::TILE_SIZE;
    destination_rectangle.y = _window_rect.y * Constants::TILE_SIZE;
    graphics.render(_sprite_sheet, &_window_tiles[0], &destination_rectangle);
    
    for (int i = 1; i < _window_rect.w - 1; i++) {
        destination_rectangle.x = (_window_rect.x + i) * Constants::TILE_SIZE;
        graphics.render(_sprite_sheet, &_window_tiles[1], &destination_rectangle);
    }
    
    destination_rectangle.x = (_window_rect.x + _window_rect.w - 1) * Constants::TILE_SIZE;
    destination_rectangle.y = _window_rect.y * Constants::TILE_SIZE;
    graphics.render(_sprite_sheet, &_window_tiles[2], &destination_rectangle);
    
    destination_rectangle.x = _window_rect.x * Constants::TILE_SIZE;
    destination_rectangle.y = (_window_rect.y + _window_rect.h - 1) * Constants::TILE_SIZE;
    graphics.render(_sprite_sheet, &_window_tiles[6], &destination_rectangle);
    
    for (int i = 1; i < _window_rect.h - 1; i++) {
        destination_rectangle.y = (_window_rect.y + i) * Constants::TILE_SIZE;
        graphics.render(_sprite_sheet, &_window_tiles[3], &destination_rectangle);
    }
    
    destination_rectangle.y = (_window_rect.y + _window_rect.h - 1) * Constants::TILE_SIZE;
    
    for (int i = 1; i < _window_rect.w - 1; i++) {
        destination_rectangle.x = (_window_rect.x + i) * Constants::TILE_SIZE;
        graphics.render(_sprite_sheet, &_window_tiles[7], &destination_rectangle);
    }
    
    destination_rectangle.x = (_window_rect.x + _window_rect.w - 1) * Constants::TILE_SIZE;
    destination_rectangle.y = (_window_rect.y + _window_rect.h - 1) * Constants::TILE_SIZE;
    graphics.render(_sprite_sheet, &_window_tiles[8], &destination_rectangle);
    
    for (int i = 1; i < _window_rect.h - 1; i++) {
        destination_rectangle.y = (_window_rect.y + i) * Constants::TILE_SIZE;
        graphics.render(_sprite_sheet, &_window_tiles[5], &destination_rectangle);
    }
    
    for (int y = 1; y < _window_rect.h - 1; y++) {
        destination_rectangle.y = (_window_rect.y + y) * Constants::TILE_SIZE;
        for (int x = 1; x < _window_rect.w - 1; x++) {
            destination_rectangle.x = (_window_rect.x + x) * Constants::TILE_SIZE;
            graphics.render(_sprite_sheet, &_window_tiles[4], &destination_rectangle);
        }
    }
}