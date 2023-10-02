#include "NPC.hpp"
NPC::NPC (std::string name, std::string description) {
    this->name = name;
    this->description = description;
}

std::string NPC::getName() const {
    return name;
}

std::string NPC::getDesc() const {
    return description;
}

std::string NPC::getMessage(int num) {
    if (messageNum > messageVector.size()-1)
        messageNum = 0;
    else
        messageNum += 1;
    return messageVector[num];
}

std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.getName();
    return os;   
}