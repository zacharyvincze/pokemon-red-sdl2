#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"
#include "animated_sprite.h"
#include "map.h"

#include <vector>

class Entity {
    public:
        Entity(Graphics& graphics, int x, int y, const std::string& file_path);
        ~Entity();

        void draw(Graphics& graphics, SDL_Rect& camera);
        void draw(Graphics& graphics);
        void update(Map& map);

        void move(int direction);
        void stop();
        void turn(int direction);
        
        int getMoveTime() { return _move_time; }
        int getCurrentTile() { return _current_tile; }

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

        SDL_Rect getEntityRect() { return _entity_rect; }
        
    protected:
        SDL_Rect _entity_rect;
        int _move_time, _speed, _frames_to_cross_one_tile, _current_tile;
        bool checkCollision(Map& map);
        DirectionFacing _direction_facing;
        MotionType _motion_type;
        int getSpriteID();
        std::vector<Sprite*> _sprites;
};

#endif // ENTITY_H