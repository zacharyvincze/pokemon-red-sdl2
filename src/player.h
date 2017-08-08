#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "npc.h"
#include <map>

class Player : public Entity {
    public:
        void update(Map& map, std::map<std::string, NPC*> NPC);
        
        Player(Graphics& graphics, int x, int y, const std::string& file_path);
        
    private:
        bool touchesWall(Map& map, std::map<std::string, NPC*> NPC);
};

#endif // PLAYER_H