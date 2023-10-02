#ifndef ITEM_HPP
#define ITEM_HPP
/* 
*/
#include <string>
#include <vector>

class NPC {
public:
    std::string name;
    std::string description;
    int messageNum;
    std::vector<std::string> messages;

    // Constructor that will accept an NPC name and description
    NPC (std::string name, std::string description);

    // getter for NPC name
    std::string getName();

    // getter for NPC description
    std::string getDesc();

    // getter for a message indicated by a message number and changes the message number appropriately
    std::string getMessage(int messageNum);
};

// overloaded stream operator -> returns NPC name
std::ostream& operator<<(std::ostream& os, const NPC& npc);
#endif