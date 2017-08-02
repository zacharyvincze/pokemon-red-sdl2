#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "npc.h"

class Player : public Entity {
    public:
        void update(Map& map, std::vector<NPC*> NPCs);
        
        Player(Graphics& graphics, int x, int y, const std::string& file_path);
        
    private:
        bool touchesWall(Map& map, std::vector<NPC*> NPCs);
};

#endif // PLAYER_H