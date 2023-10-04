#include "Game.hpp"
#include <random>
#include <functional>

Game::Game () {
    create_world();
    Location curLoc = random_location();
    std::cout << curLoc << std::endl;
    weight = 0;
    elfCalorieGoal = 5000;
    commandMap = setup_commands();
}

void Game::create_world () {
    // creation of all locations
    Location Kirkhoff("Kirkhoff", "Has food and club meeting areas.");
    Location Mak("Mackinac Hall", "Where computer science majors go to cry");
    Location Clocktower("Carillon Clocktower", "Scares you with a bell every 15 minutes");
    Location littleMakBridge("Little Mak Bridge", "Not so little when you're scared of heights");

    Kirkhoff.add_location("North", Clocktower);
    Kirkhoff.add_location("East", littleMakBridge);
    littleMakBridge.add_location("North", Mak);

    // add locations to the location vector
    locationVector.push_back(Kirkhoff);
    locationVector.push_back(Mak);
    locationVector.push_back(Clocktower);
    locationVector.push_back(littleMakBridge);


    // create Items
    Item sushi ("Sushi", "Raw Fish... ew", 500, 2.0f);
    Item clubPamphlet ("Club Pamphlet", "This is a pamphlet for the ... lettuce eating club???", 0, 1.0f);
    Item laptop ("Laptop", "It looks like whoever used this laptop has memory leaks in their C code.", 0, 3.0f);
    Item Coffee ("Coffee", "The only Java I like", 20, 1.0f);

    // add items to corresponding location
    Kirkhoff.add_item(sushi);
    Kirkhoff.add_item(clubPamphlet);
    Mak.add_item(laptop);

    // create NPCs
    NPC PODStoreEmployee("POD store employee", "supplier of energy drinks");
    NPC CoffeShopEmployee("Coffee Shop employee", "makes the best coffee in all of Kirkhoff");

    // add NPCs to Location
    Kirkhoff.add_npc(CoffeShopEmployee);
    Mak.add_npc(PODStoreEmployee); 
}

void Game::talk (std::vector<std::string> target) {
    std::cout << "talk" << std::endl;
}

void Game::meet (std::vector<std::string> target) {
    std::cout << "meet" << std::endl;
}

void Game::take (std::vector<std::string> target) {
    std::cout << "take" << std::endl;
}

void Game::give (std::vector<std::string> target) {
    std::cout << "give" << std::endl;
}

std::map<std::string, void(*)(std::vector<std::string>)> Game::setup_commands() {
    std::map<std::string, void(*)(std::vector<std::string>)> commmandsMap;
    // mapping keywords to their corresponding function/command
    commmandsMap["talk"] = talk;
    commmandsMap["meet"] = meet;
    commmandsMap["take"] = take;
    commmandsMap["give"] = give;

    return commmandsMap;
}

Location Game::random_location () {
    // used chatGPT to figure out the syntax with the <random> library
    std::random_device rd; // Seed the random number generator
    std::mt19937 mt(rd()); // Mersenne Twister engine

    // Define uniform distribution for integers between 0 and the size of the locationVector
    std::uniform_int_distribution<int> distribution(0, locationVector.size()-1);

    // Generate random number
    int randNum = distribution(mt);
    
    return locationVector[randNum];
}

void Game::play(){
    //Print msg descriing game
    std::cout << "Message Describing game (still needed)" << std::endl;

    //Have a loop that tells user to enter command
    //Split user input into vector of words
    while (inProgress) {

        std::cout << "Enter commands to interact with the game." << std::endl;
        std::cout << "> "; //shows that user can inupt text 
        std::string user_Response;
        std::getline(std::cin, user_Response);

        //if token not empty 
        if(!tokens.empty()){
            // Split user input into vector of words
            std::vector<std::string> tokens;
            std::tokens = std::split(user_Response, );//user_Response.split();
            std::string command = tokens[0];
            //removes first word in element becuse thats command
            del(tokens[0])
            //Makes target whatever string is after the first word
            target = ' '.join(tokens)
            //Example below
            //should look like this if user enters "talk ball of light"
            //command = talk,
            //target  = ball of light

            //TODO 
            //idk if right sentax
            //call map command my useing this key

            //TESTING PURPUSES REMOVE
            if(command = "quit"){
                inProgress = 0
            }


            if (commandMap.find(command) != commandMap.end()) {
                std::cout << "Command is recognized." << std::endl;
            } 
            else {
                std::cout << "Command not recognized." << std::endl;
            }
            //pass target as perameter to it 
            //if map for command does not exits 
            //tell user there command does not exist

        }
        
    }

    //TODO
    //Check if elf has enough calories
    //if yes
    std::cout << "success" << std::endl;
    //quit game

    //if no
    std::cout << "failure" << std::endl;
    //quit game
}
