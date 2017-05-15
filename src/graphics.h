#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <string>
#include <map>

class Graphics {
        typedef SDL_Texture* SurfaceID;

    public:
        Graphics();
        ~Graphics();

        SurfaceID loadImage(const std::string& filePath);

        void render(SurfaceID source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

        void present();
        void clear();

    private:
        typedef std::map<std::string, SDL_Texture*> SpriteMap;
        SpriteMap mSpriteSheets;
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
};

#endif // GRAPHICS_H
