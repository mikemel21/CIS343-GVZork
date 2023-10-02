#include "Item.hpp"
#include "NPC.hpp"
#include "Location.hpp"
//! THIS IS JUST A TESTING FILE!!! DELETE WHEN FINISHED
// NO PERMANENT CODE WILL GO HERE
int main() {
    Item a("Sword", "rusty and old", 100, 123);
    Item anotherItem("another item", "just another item", 50, 100);
    NPC b("a dude", "I am a dude");
    NPC n("another NPC", "just another npc");
    Location c("Palace", "Just a castle but prettier");

    c.add_item(a);
    c.add_item(anotherItem);
    c.add_npc(b);
    c.add_npc(n);

    std::cout << c << std::endl;
}