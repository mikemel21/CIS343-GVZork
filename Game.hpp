#ifndef GAME_HPP
#define GAME_HPP
// Holds all logic for game instance

#include "Item.hpp"
#include "Location.hpp"

class Game {
    private:  
        std::vector<std::reference_wrapper<Item>> itemVector; // vector that holds all the items the player has
        std::vector<std::reference_wrapper<Location>> locationVector; // vector that holds reference_wraps to all locations in the world
        std::vector<Location> locs; // vector that holds the location objects in the world
        int weight; // stores the player's weight
        int elfCalorieGoal; // stores the # of calories the elf needs to save the campus
        bool inProgress = true; // bool that stores whether the game is in progress
        // stores player's current location
        Location cur;
        Location& curLoc = cur;
    public:
        std::map<std::string, void (Game::*)(std::vector<std::string>)> commandMap; //! Not sure if correct
        // Constructor with no parameters
        Game();

        // Create all Locations, Items, and NPCs in the game
        void create_world();

        // Keys -> 
        // Values -> names of the functions that will be called
        // must return the map
        std::map<std::string, void(Game::*) (std::vector<std::string>)> setup_commands();

        // chooses random Location from locations vector and returns that location
        Location random_location();

        /* core game loop. First prints message with game description thaen calls 
           the method to vector all commands */
        void play();

        /* prints out a help message and all the commands from the command map's keys; 
           Also posts current time */
        void show_help();

        /* Checks if provided NPC is in the current room; if it is, call the NPC's 
           get_message method and print it */
        void talk (std::vector<std::string> target);

        // Check if NPC is in the room and it will print the NPC's description
        void meet (std::vector<std::string> target);

        /* if the target is in the room, it will remove it from the room's
            inventory, add it to the user's inventory, and add its wright to the user's weight */
        void take (std::vector<std::string> target);

        /* Removes target item from user's inventory, adds it to the current location's incentroy 
           and decreases user weight*/
        void give (std::vector<std::string> target);

        /* Sets current location's visited status to true, 
           checks if the player has >30 weight and prints message and returns if true,
           else, it checks if provided direction exists in the current location's neighbor map and sets 
           the current location equal to the value from the map*/
        void go (std::vector<std::string> target);

        /* Print all items the player is carrying and the current amount of weight*/
        void show_items (std::vector<std::string> target);

        /* Print the current location, vector of Items in the location or a message if there arent any,
           a vector of NPC's in the room or the message "You are alone" if empty, and a vector of 
           directions that a player can go. If a location has been visited previously, pritn the direction
           and location; otherwise, print the direction */
        void look (std::vector<std::string> target);

        /* Print a failure message and exits the game*/
        void quit (std::vector<std::string> target);

        //! CREATE TWO ADDITIONAL COMMAND FUNCTIONS
};

#endif