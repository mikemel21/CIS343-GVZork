#include "Location.hpp"

Location::Location () {
    this->name = "";
    this->description = "";
}

Location::Location (const std::string& name, const std::string& description) {
    this->name = name;
    this->description = description;
}

std::map<std::string, std::reference_wrapper<Location> > Location::get_locations () {
    return neighbors;
}

void Location::add_location(std::string direction, std::reference_wrapper<Location> location) {
    if (direction.empty()) 
        throw std::invalid_argument("direction cannot be empty.");

    if (neighbors.count(direction) > 0)
        throw std::invalid_argument("There is already a locatio in that direction.");
    
    neighbors.insert({direction, location});
}

void Location::add_npc(NPC npc) {
    NPCVector.push_back(npc);
}

std::vector<std::reference_wrapper<NPC> > Location::get_npcs () const {
    return NPCVector;
}

void Location::add_item (Item item) {
    ItemVector.push_back(item);
}

std::vector<std::reference_wrapper<Item> > Location::get_items() const{
    return ItemVector;
}

void Location::set_visited() {
    visited = true;
}

bool Location::get_visited() const {
    return visited;
}

std::ostream& operator<<(std::ostream& os, std::reference_wrapper<Location>  location) {
    os << location.get().name << " - " << location.get().description << std::endl << std::endl;
    os << "You see the following NPCs: " << std::endl;
    // print npc vector in bulleted list
    for (NPC npc : location.get().NPCVector) {
        os << "    - " << npc << std::endl;
    }
    os << std::endl << std::endl << "You see the following Items: " << std::endl;
    for (Item item : location.get().ItemVector) {
        os << "    - " << item << std::endl;
    }
    os << std::endl << std::endl << "You can go to the following Directions: " << std::endl;
    for (const auto& pair : location.get().neighbors) {
        os << "    -" << pair.first << " - " << pair.second.get().name << " (";
        // print Visited if visited == 1 and Not Visited if visited == 0
        if (pair.second.get().get_visited() == 0) {
            os << "Not Visited" << ")" << std::endl;
        } else {
            os << "Visited" << ")" << std::endl;
        }
    }

    return os;   
}