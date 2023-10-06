#ifndef LOCATION_HPP
#define LOCATION_HPP

/* Each Location is a place on campus that can be visited
    PARAMS:
    - Name : string
    - Description : string
    - Whether Location has been visited or not : bool
    - Map of neighbors
    - Vector of NPCs
    - Vector of Items
*/
#include <map>
#include <string>
#include <vector>
#include "NPC.hpp"
#include "Item.hpp"

class Location {
private:
    std::string name;
    std::string description;
    bool visited;
    std::map<std::string, std::reference_wrapper<Location> > neighbors;
    std::vector<NPC> NPCVector;
    std::vector<Item> ItemVector;
public:
    Location ();
    // Constructor that takes a Location name and description
    Location (const std::string& name, const std::string& description);

    // Returns the neighbors map
    std::map<std::string, std::reference_wrapper<Location> > get_locations ();

    // Adds location parameter into the map with the provided direction string (nonempty)
    void add_location(std::string direction, std::reference_wrapper<Location> location);

    // Adds NPC to the Location's NPC vector
    void add_npc (NPC npc);

    // Getter to return the vector of NPCs
    std::vector<NPC> get_npcs() const;

    // Adds Item to the Location's Item vector
    void add_item(Item item);

    // Getter to return the vector of Items
    std::vector<Item> get_items() const;

    // Setter that changes the visited variable to true; once location is visited, it can no longer be false
    void set_visited();

    // Getter that returns whether or not the Location has been visited
    bool get_visited() const;

    /* overloaded stream operator -> returns info in below format:
    Name - Description

    You see the following NPCs:
    - List NPCs (in format from their constructor)

    You see the following Items:
    - List items (in format from their constructor)

    You can go in the following Directions:
    - direction - location (whether it has been visited)

    */
    friend std::ostream& operator<<(std::ostream& os, std::reference_wrapper<Location> location);
};
#endif