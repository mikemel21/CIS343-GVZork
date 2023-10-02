#ifndef NPC_HPP
#define NPC_HPP
/* NPC class represents info about a character in a Location;
   NPCs have a:
    - name
    - description
    - message number
    - vector of their messages
*/
/*NOTES:
    - Every time a player talks to an NPC, messageNum increments by 1
        -> results in the next message in the vector being printed the next time the player speaks to the character
    - When message number is > the size of the message vector, it must go back to 0
*/

#include <string>
#include <vector>

class NPC {
public:
    std::string name;
    std::string description;
    int messageNum = 0; // increases by 1 evertime player talks to the NPC; goes back to 0 after it is > the message vector
    std::vector<std::string> messageVector;

    // Constructor that will accept an NPC name and description
    NPC (const std::string& name, const std::string& description);

    // getter for NPC name
    std::string getName() const;

    // getter for NPC description
    std::string getDesc() const;

    // getter for a message indicated by a message number and changes the message number appropriately
    std::string getMessage(int num);
};

// overloaded stream operator -> returns NPC name
std::ostream& operator<<(std::ostream& os, const NPC& npc);
#endif