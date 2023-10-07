#include "NPC.hpp"
#include <stdexcept>
/*
    Michael Melei
    Justin Burch
*/
NPC::NPC (const std::string& name, const std::string& description) {
    this->name = name;
    this->description = description;

    // exception handlingL: throw exception if name or description are empty
    if (name.empty())
        throw std::invalid_argument("NPC Name cannot be empty.");
    if (description.empty())
        throw std::invalid_argument("NPC Description cannot be empty");
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