#include "Game.hpp"
#include <random>
#include <functional>

Game::Game () {
    create_world();
    locationVector = std::vector<std::reference_wrapper<Location> >(locs.begin(), locs.end());
    curLoc = random_location();
    //std::cout << curLoc << std::endl;
    weight = 0;
    elfCalorieGoal = 5000;
    commandMap = setup_commands();
}

void Game::create_world () {
    // create/add locations to the location vector
    // kirkhoff -> locationVector[0]
    this->locs.push_back(Location ("Kirkhoff", "Has food and club meeting areas."));
    // Mak -> locationVector[1]
    this->locs.push_back(Location ("Mackinac Hall", "Where computer science majors go to cry"));
    // Clocktower -> locationVector[2]
    this->locs.push_back(Location ("Carillon Clocktower", "Scares you with a bell every 15 minutes"));
    // Bridge -> locationVector[3]
    this->locs.push_back(Location ("Little Mak Bridge", "Not so little when you're scared of heights"));

    // add clocktower as neighbor to Kirkhoff
    locs[0].add_location("North", locs[2]);
    // add Mak bridge as neighbor to Kirkhoff
    locs[0].add_location("East", locs[3]);
    // add Mak Hall as a neighbor to Mak Bridge
    locs[3].add_location("North", locs[1]);

    //Item Coffee ("Coffee", "The only Java I like", 20, 1.0f);

    // Kirkhoff Items
    locs[0].add_item(Item ("Sushi", "Raw Fish... ew", 500, 2.0f));
    locs[0].add_item(Item ("Club Pamphlet", "This is a pamphlet for the ... lettuce eating club???", 0, 1.0f));

    // Mak Items
    locs[1].add_item(Item ("Laptop", "It looks like whoever used this laptop has memory leaks in their C code.", 0, 3.0f));

    // Kirkhoff NPCs
    locs[0].add_npc(NPC ("Coffee Shop employee", "makes the best coffee in all of Kirkhoff"));

    // Mak NPC's
    locs[1].add_npc(NPC ("POD store employee", "supplier of energy drinks")); 
}

void Game::talk (std::vector<std::string> target) {
    std::cout << "talk" << std::endl;
}

void Game::meet (std::vector<std::string> target) {
    //Item item = std::find();
    std::cout << "meet" << std::endl;
}

void Game::take (std::vector<std::string> target) {
    std::cout << "take" << std::endl;
}

void Game::give (std::vector<std::string> target) {
    std::cout << "give" << std::endl;
}

std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setup_commands() {
    std::map<std::string, void(Game::*) (std::vector<std::string>) > commands;
    // mapping keywords to their corresponding function/command
    commands["talk"] = &Game::talk;
    commands["meet"] = &Game::meet;
    commands["take"] = &Game::take;
    commands["give"] = &Game::give;

    //*commandMap["talk"]({"test"});
    
    return commandMap;
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

// void Game::play(){
//     //Print msg descriing game
//     std::cout << "Message Describing game (still needed)" << std::endl;

//     //Have a loop that tells user to enter command
//     //Split user input into vector of words
//     while (inProgress) {

//         std::cout << "Enter commands to interact with the game." << std::endl;
//         std::cout << "> "; //shows that user can inupt text 
//         std::string user_Response;
//         std::getline(std::cin, user_Response);

//         //if token not empty 
//         if(!tokens.empty()){
//             // Split user input into vector of words
//             std::vector<std::string> tokens;
//             std::tokens = std::split(user_Response, );//user_Response.split();
//             std::string command = tokens[0];
//             //removes first word in element becuse thats command
//             del(tokens[0])
//             //Makes target whatever string is after the first word
//             target = ' '.join(tokens)
//             //Example below
//             //should look like this if user enters "talk ball of light"
//             //command = talk,
//             //target  = ball of light

//             //TODO 
//             //idk if right sentax
//             //call map command my useing this key

//             //TESTING PURPUSES REMOVE
//             if(command = "quit"){
//                 inProgress = 0
//             }


//             if (commandMap.find(command) != commandMap.end()) {
//                 std::cout << "Command is recognized." << std::endl;
//             } 
//             else {
//                 std::cout << "Command not recognized." << std::endl;
//             }
//             //pass target as perameter to it 
//             //if map for command does not exits 
//             //tell user there command does not exist

//         }
        
//     }

//     //TODO
//     //Check if elf has enough calories
//     //if yes
//     std::cout << "success" << std::endl;
//     //quit game

//     //if no
//     std::cout << "failure" << std::endl;
//     //quit game
// }
