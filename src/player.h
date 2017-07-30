#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "animated_sprite.h"
#include "map.h"

#include <vector>

class Player {
    public:
        Player(Graphics& graphics, int x, int y, const std::string& file_path);
        ~Player();

        void draw(Graphics& graphics, SDL_Rect& camera);
        void draw(Graphics& graphics);
        void update(Map& map);

        void move(int direction);
        void stop();
        void turn(int direction);
        
        int getMoveTime() { return _move_time; }

        enum MotionType {
            WALKING,
            STANDING
        };

        enum DirectionFacing {
            NORTH,
            SOUTH,
            WEST,
            EAST
        };

        SDL_Rect getPlayerRect() { return _player_rect; }

    private:
        int getSpriteID();

        DirectionFacing _direction_facing;
        MotionType _motion_type;
        
        void correctCollision(Map& map);
        
        int _move_time, _speed, _frames_to_cross_one_tile;
        std::vector<Sprite*> _sprites;
        SDL_Rect _player_rect;
};

#endif // PLAYER_H
