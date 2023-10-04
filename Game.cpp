#include "Game.hpp"

Game::Game () {
    //curLoc = random_location();
    weight = 0;
    elfCalorieGoal = 5000;
    commands = setup_commands();
    create_world();
}

// Game::create_world () {

// }