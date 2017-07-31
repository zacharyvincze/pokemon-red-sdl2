#ifndef NPC_H
#define NPC_H

#include "entity.h"

class NPC : public Entity {
    public:

        NPC(Graphics& graphics, int x, int y, const std::string& file_path, std::string message);
    
        std::string getMessage() { return mMessage; }
    
    private:
        std::string mMessage;
        int _elapsed_frames;
    
};

#endif // NPC_H