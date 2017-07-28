#ifndef NPC_H
#define NPC_H

#include "player.h"

class NPC : public Player {
    public:

        NPC(Graphics& graphics, int x, int y, const std::string& file_path, std::string message);
    
        std::string getMessage() { return mMessage; }
    
    private:
        std::string mMessage;
    
};

#endif // NPC_H