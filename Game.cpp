#include "Game.hpp"
#include <random>
#include <functional>
#include <sstream>

/*
    Michael Melei
    Justin Burch
*/

Game::Game () {
    create_world();
    locationVector = std::vector<std::reference_wrapper<Location> >(locs.begin(), locs.end());
    //cur = random_location();
    cur = locationVector[0];
    curLoc = cur;
    weight = 0;
    elfCalorieGoal = 5000;
    commandMap = setup_commands();

    play();
}

void Game::create_world () {
    // create/add locations to the location vector
    Location Kirkhoff ("Kirkhoff", "Has food and club meeting areas.");
    Location MackinacHall ("Mackinac Hall", "Where computer science majors go to cry");
    Location Clocktower ("Carillon Clocktower", "Scares you with a bell every 15 minutes");
    Location Bridge ("Little Mak Bridge", "Not so little when you're scared of heights");
    Location BlueConnection ("The Blue Connecion", "Food, classrooms. There's always something in here for you.");
    Location WaterFountain ("Water Fountain","I wonder if there are fish in there...");
    Location Gym ("Gym", "You'll probably find protein powder in here.");
    Location Manitou ("Manitou Hall", "Still don't know the difference between this and Makinac hall");

    this->locs.push_back(Kirkhoff);
    this->locs.push_back(MackinacHall);
    this->locs.push_back(Clocktower);
    this->locs.push_back(Bridge);
    this->locs.push_back(BlueConnection);
    this->locs.push_back(WaterFountain);
    this->locs.push_back(Gym);
    this->locs.push_back(Manitou);

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
    NPC ProfessorWoodring("Professor Woodring", "Will sometimes respond to 'Mustang'.");
    ProfessorWoodring.messageVector.push_back("Test message");

    this->locs[1].add_npc(NPC ("POD store employee", "supplier of energy drinks"));
    this->locs[1].add_npc(ProfessorWoodring);

    //*Gym NPC's
    this->locs[6].add_npc(NPC ("Gym bro", "I wonder if he knows where food is."));

    //*Blue Connection NPC's
    this->locs[4].add_npc(NPC ("Hearth employee", "Depending on their mood you either will get a big or small portion."));
}

void Game::talk (std::vector<std::string> target) {
    std::cout << "talk" << std::endl;
    // Get NPCs in the current room using the get_npcs() method
    std::vector<NPC> currentRoomNPCs = curLoc.get_npcs();

    // Check if the provided NPC is in the current room 
        bool in_room = false;
        std::string npcName = target[0];

        for (NPC& npc : curLoc.get_npcs()) { //not really sure how this 4 loop works
            if (npc.getName() == npcName) {
                in_room = true;
                std::cout << "You talk to " << npc.getName() << ": " << npc.getMessage(npc.messageNum) << std::endl;
                break;
            }
        }

        if (!in_room) {
            std::cout << npcName << " is not in the current room." << std::endl;
        }
}

void Game::meet (std::vector<std::string> target) {
    if (target.empty())
        std::cout << "Invalid NPC." << std::endl;
    else{
        std::string npcName = target[0];
        
        for (const NPC& npc : curLoc.get_npcs()) {
            if (npc.getName() == npcName) {
                std::cout << "You met " << npc << ": " << npc.getDesc();
                return;
            }
        }
        std::cout << "An NPC named " << npcName << "does not exist" << std::endl;
    }
}

void Game::take (std::vector<std::string> target) {
    std::string targetItem = target[0];

    auto it = std::find_if(curLoc.get_items().begin(), curLoc.get_items().end(),
                    [targetItem](const Item& item) { return item.name == targetItem; });

    if (it != curLoc.get_items().end()) {
        // Erase the item from the vector
        curLoc.get_items().erase(it);
        //itemVector.push_back(*it);
        weight += it->weight;
        std::cout << "Item '" << targetItem << "' was taken" << std::endl;
    } else {
        std::cout << "Item '" << targetItem << "' not found." << std::endl;
    }       
}

void Game::give (std::vector<std::string> target) {
    // check if target is in player's inventory
    if (itemVector.empty()) {
        std::cout << "You have no items." << std::endl;
    } else {

    }
}

void Game::look (std::vector<std::string> target) {
    // print items in the current location
    if (curLoc.get_items().empty()) {
        // print if no items
        std::cout << "There are no items in this location." << std::endl;
    } else {
        std::cout << "Items in this location: " << std::endl;
        for (const Item& item : curLoc.get_items())
            std::cout << "- " << item << std::endl;
        std::cout << std::endl;
    }

    // print NPCs
    if (curLoc.get_npcs().empty()) {
        std::cout << "You are alone." << std::endl;
    } else {
        std::cout << "NPCs in this location: " << std::endl;
        for (const NPC& npc : curLoc.get_npcs())
            std::cout << "- " << npc << std::endl;
        std::cout << std::endl;
    }
    // Print Locations
    std::cout << "Where to go: " << std::endl;
    for (const auto& loc : curLoc.get_locations()) {
        // if location was visited, print the direction and location name
        if (loc.second.get().get_visited()) {
            std::cout << "- " << loc.first << "- " << loc.second.get().name << std::endl;
        } else {
            // if not visited, print only direction
            std::cout << "- " << loc.first << std::endl;
        }
    }
}

void Game::teleport (std::vector<std::string> target) {
    bool isFound = false;
    if (target.empty()) {
        std::cout << "Invalid location." << std::endl;
    }
    std::string targetLocation = target[0];
    for (const auto& loc : curLoc.get_locations()) {
        if (targetLocation == loc.second.get().name) {
            isFound = true;
            cur = loc.second;
            break;
        }
    }

    if (!isFound)
        std::cout << "Location not found." << std::endl;
}

void Game::eatItem (std::vector<std::string> target) {
    std::string targetItem = target[0];
    // utilized ChatGPT for the auto it lambda
    auto it = std::find_if(itemVector.begin(), itemVector.end(),
                    [targetItem](const Item& item) { return item.name == targetItem; });

    if (it != itemVector.end()) {
        // Erase the item from the vector
        itemVector.erase(it);
        weight -= it->weight;
        std::cout << "Item '" << targetItem << "' was yummy." << std::endl;
    } else {
        std::cout << "Item '" << targetItem << "' not found." << std::endl;
    }       
    
}

std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setup_commands() {
    std::map<std::string, void(Game::*) (std::vector<std::string>) > commands;
    // mapping keywords to their corresponding function/command
    commands["talk"] = &Game::talk;
    commands["meet"] = &Game::meet;
    commands["take"] = &Game::take;
    commands["give"] = &Game::give;
    commands["look"] = &Game::look;
    commands["go"] = &Game::go;
    commands["items"] = &Game::show_items;
    commands["help"] = &Game::show_help;
    commands["teleport"] = &Game::teleport;
    commands["eat"] = &Game::eatItem;
    commands["quit"] = &Game::quit;
    
    return commands;
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

void Game::go (std::vector<std::string> target) {
    curLoc.set_visited();
    if (weight > 30) {
        std::cout << "Your weight is over 30." << std::endl;
        return;
    }
    std::string targ = target[0];
    for (const auto& entry : curLoc.get_locations()) {
        // if target matches anything in the neighbors vector
        if (entry.second.get().name == targ) {
            // set curLoc to the target
            curLoc = entry.second;
            break;
        }
    }
}

void Game::show_items (std::vector<std::string> target) {
    std::cout << "Your Items: " << std::endl;
    for (const Item& item : itemVector) {
        std::cout << "\t- " << item << std::endl;
    }
    std::cout << "Your Weight: " << weight << std::endl;
}

void Game::show_help (std::vector<std::string> target) {
    std::cout << "Available Commands: " << std::endl;
    for (const auto& com : commandMap) {
        std::cout << "- " << com.first << std::endl;
    }
}

void Game::quit (std::vector<std::string> target) {
    inProgress == false;
    if (curCals >= 500) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "You have failed..." << std::endl;
    }
    std::exit(0);
}

void Game::play() {
    //Print msg describing game
    std::cout << "Welcome to GVZork!\n" << "The goal of this game is to " << 
                  "travel throughout the Grand Valley Campus and collect "<<
                  "items to give to the Elf.\n" <<
                  "In order to complete the game, you must give the elf enough calories!\n" << std::endl;
    show_help({""});

    // put all commands in a vector
    std::vector<std::pair<std::string, void(Game::*)(std::vector<std::string>)> > commandVector;
    for (auto& pair : commandMap) {
        commandVector.push_back(pair);
    }

    // Tokens vector
    std::vector<std::string> tokens;

    //Have a loop that tells user to enter command
    //Split user input into vector of words
    while (inProgress) {
        std::cout << "Enter commands to interact with the game." << std::endl;
        std::cout << "> "; //shows that user can inupt text 
        std::string user_Response;
        std::getline(std::cin, user_Response);
        std::istringstream iss(user_Response);
        std::string word;
        std::vector<std::string> token;        
        
        while (iss >> word) {
            token.push_back(word);
        }

        //if token not empty 
       if(!token.empty()){
            // Split user input into vector of words
            //tokens = std::split(user_Response, );//user_Response.split();
            std::string command = token[0];

            //removes first word in element becuse thats command
            token.erase(token.begin());

            // Initialize the concatenated string with the first word
            std::string target = token.empty() ? "" : token[0];
            // Concatenate the remaining words, adding a space before each word except the last one
            for (size_t i = 1; i < token.size(); ++i) {
                target += " " + token[i];
            }

            auto it = commandMap.find(command);
            if (it != commandMap.end()) {
                (this->*(it->second))({target});  
            } else {
                std::cout << "Invalid command." << std::endl;
            }
        }
    }
}
