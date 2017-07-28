#include "npc.h"

NPC::NPC(Graphics& graphics, int x, int y, const std::string& file_path, std::string message) :
    Player(graphics, x, y, file_path) {
    mMessage = message;
}