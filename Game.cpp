#include "Game.hpp"
#include <random>
#include <functional>

Game::Game () {
    create_world();
    locationVector = std::vector<std::reference_wrapper<Location> >(locs.begin(), locs.end());
    cur = random_location();
    curLoc = cur;
    weight = 0;
    elfCalorieGoal = 5000;
    commandMap = setup_commands();

    test();
}

void Game::test () {
    look({""});
}

void Game::create_world () {
    // create/add locations to the location vector
    // kirkhoff -> locationVector[0]
    this->locs.push_back(Location("Kirkhoff", "Has food and club meeting areas."));
    // Mak -> locationVector[1]
    this->locs.push_back(Location("Mackinac Hall", "Where computer science majors go to cry"));
    // Clocktower -> locationVector[2]
    this->locs.push_back(Location("Carillon Clocktower", "Scares you with a bell every 15 minutes"));
    // Bridge -> locationVector[3]
    this->locs.push_back(Location("Little Mak Bridge", "Not so little when you're scared of heights"));
    // Blue Connection -> locationVector[4]
    this->locs.push_back(Location("The Blue Connecion", "Food, classrooms. There's always something in here for you."));
    // Water fountain -> locationVector[5]
    this->locs.push_back(Location("Water Fountain","I wonder if there are fish in there..."));
    // Gym -> locationVector[6]
    this->locs.push_back(Location("Gym", "You'll probably find protein powder in here."));
    // Manitou -> locationVector[7]
    this->locs.push_back(Location("Manitou Hall", "Still don't know the difference between this and Makinac hall"));

    // add clocktower as neighbor to Kirkhoff
    this->locs[0].add_location("North", locs[2]);
    // add Mak bridge as neighbor to Kirkhoff
    this->locs[0].add_location("North East", locs[3]);
    // Water fountain neighbor to Kirkhoff
    this->locs[0].add_location("East", locs[5]);
    // Gym neighbor to Kirkhoff
    this->locs[0].add_location("Northwest", locs[6]);
    // Blue Connection neighbor to Kirkhoff
    this->locs[0].add_location("Southwest", locs[4]);

    // add Manitou as a neighbor to Mak
    this->locs[1].add_location("West", locs[7]);
    // Bridge neighbor to Mak
    this->locs[1].add_location("South", locs[3]);
    
    // Kirkhoff neighbor to clocktower
    this->locs[2].add_location("South", locs[0]);
    // Gym neighbor to clocktower
    this->locs[2].add_location("West", locs[6]);

    // add Mak Hall as a neighbor to Mak Bridge
    this->locs[3].add_location("North", locs[1]);
    // Water fountain neighbor to bridge
    this->locs[3].add_location("South", locs[5]);
    // Manitou neighbor to Bridge
    this->locs[3].add_location("Northeast", locs[7]);

    // Gym neighbor to Blue Connection
    this->locs[4].add_location("North", locs[6]);
    // Kirkhoff neighbor to Blue Connection
    this->locs[4].add_location("Northeast", locs[0]);

    // Kirkhoff neighbor to waterfountain
    this->locs[5].add_location("West", locs[0]);
    // Bridge neighbor to waterfountain
    this->locs[5].add_location("East", locs[3]);

    // Kirkhoff neighbor to Gym
    this->locs[6].add_location("Southeast", locs[0]);
    // Clocktower neighbor to Gym
    this->locs[6].add_location("East", locs[2]);
    // Blue Connection neighbor to Gym
    this->locs[6].add_location("South", locs[4]);

    // Mak neighbor to Manitou
    this->locs[7].add_location("East", locs[1]);
    // Bridge neighbor to Manitou
    this->locs[7].add_location("South", locs[3]);

    //* Kirkhoff Items
    // sushi
    this->locs[0].add_item(Item ("Sushi", "Raw Fish... ew", 500, 2.0f));
    // club pamphlet
    this->locs[0].add_item(Item ("Club Pamphlet", "This", 0, 1.0f));
    // subway sandwich
    this->locs[0].add_item(Item ("Subway sandwich", "teste", 200, 2.5f));

    //* Mak Items
    // laptop
    this->locs[1].add_item(Item ("Laptop", "It looks like whoever used this laptop has memory leaks in their C code.", 0, 3.0f));
    // coffee
    this->locs[1].add_item(Item ("Coffee", "The only Java I like", 20, 1.0f));

    //* Blue Connection Items
    // Laker Bowl
    this->locs[4].add_item(Item ("Laker Bowl", "Mashed potatoes, chicken, and corn", 400, 3.5f));
    // Quesadilla
    this->locs[4].add_item(Item ("Quesadilla", "The secret menu of the POD store", 450, 3.0f));

    //* Gym Items
    // Protein Powder
    this->locs[6].add_item(Item ("Protein Powder", "Supposedly taste like chocolate but is more like chalk.", 250, 4.0f));
    // Dumbbell
    this->locs[6].add_item(Item ("Dumbbell", "Do I have to carry this around?", 0, 6.0f));

    //* Waterfountain Items
    // fish
    this->locs[5].add_item(Item ("Rotting fish", "Oh, I guess there are fish in there... please don't eat this", 300, 2.0f));


    //*Kirkhoff NPCs
    this->locs[0].add_npc(NPC ("Coffee Shop employee", "makes the best coffee in all of Kirkhoff"));

    //*Mak NPC's
    this->locs[1].add_npc(NPC ("POD store employee", "supplier of energy drinks"));
    this->locs[1].add_npc(NPC ("Professor Woodring", "Will sometimes respond to 'Mustang'."));

    //*Gym NPC's
    this->locs[6].add_npc(NPC ("Gym bro", "I wonder if he knows where food is."));

    //*Blue Connection NPC's
    this->locs[4].add_npc(NPC ("Hearth employee", "Depending on their mood you either will get a big or small portion."));
}

void Game::talk (std::vector<std::string> target) {
    //std::cout << "talk" << std::endl;
    // Get NPCs in the current room using the get_npcs() method
    // std::vector<NPC> currentRoomNPCs = curLoc.get_npcs();

    // // Check if the provided NPC is in the current room 
    //     bool in_room = false;
    //     for (NPC& npc : currentRoomNPCs) { //not really sure how this 4 loop works
    //         if (npc.getName().compare(target.) == 0) {
    //             in_room = true;
    //             std::cout << "You talk to " << target << ": " << npc.getMessage(npc.messageNum) << std::endl;
    //             break;
    //         }
    //     }

    //     if (!in_room) {
    //         std::cout << target << " is not in the current room." << std::endl;
    //     }
}

void Game::meet (std::vector<std::string> target) {
    //Item item = std::find();
    std::cout << "meet" << std::endl;
}

void Game::take (std::vector<std::string> target) {
    std::cout << "take" << std::endl;
}

void Game::give (std::vector<std::string> target) {
    // check if target is in player's inventory
    // auto i = std::find(curLoc.get_items().begin(), curLoc.get_items().end(), target);
    // if (i != itemVector.end()) {
    //     itemVector.erase(i);
    // } else {
    //     std::cout << "This item is not in your inventory." << std::endl;
    // }
}

void Game::look (std::vector<std::string> target) {
    std::cout << "Test" << std::endl;
    // print items in the current location
    if (curLoc.get_items().empty()) {
        std::cout << "There are no items in this location." << std::endl;
    } else {
        std::cout << "Here are the items in this location: " << std::endl;
        std::cout << curLoc.get_items() << std::endl;
    }

    // print NPCs
    if (curLoc.get_npcs().empty()) {
        std::cout << "You are alone." << std::endl;
        //curLoc.get_locations().
    } else {
        curLoc.get_npcs();
    }
}

void teleport (std::vector<std::string> target){
    std::cout << "teleported." << std::endl;
}

void showVisited (std::vector<std::string> target) {
    std::cout << "visited place: " << std::endl;
}

std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setup_commands() {
    std::map<std::string, void(Game::*) (std::vector<std::string>) > commands;
    // mapping keywords to their corresponding function/command
    commands["talk"] = &Game::talk;
    commands["meet"] = &Game::meet;
    commands["take"] = &Game::take;
    commands["give"] = &Game::give;
    
    return commandMap;
}

Location Game::random_location() {
    // Chat GPT assisted in the making of this function as well as the comments on lines 174 and 176
    // Seed the random number generator
    std::random_device rd;
    // Mersenne Twister engine
    std::mt19937 mt(rd());

    // Define uniform distribution for integers between 0 and the size of the locationVector
    std::uniform_int_distribution<int> distribution(0, locationVector.size() - 1);

    // Generate a random number
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
