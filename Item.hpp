#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
/* An Item is an object the player will encounter along the way;
    Items have:
        - a name (non-empty string)
        - calorie amount (0 if not edible; cannot be < 0 or > 1000) : INT
        - a weight (must be between 0 and 500) : FLOAT
        - a description (non-empty string)
*/
class Item {
public:
    std::string name;
    std::string description;
    int calories;
    float weight;
    // Constructor to create an Item object with specific name, description, calories, and weight
    Item (std::string nme, std::string desc, int cals, float wgt);
};

// stream overloader that will print/return Item in format NAME (X calories) - X lb - DESCRIPTION
// Note: Used ChatGPT to gain an understanding of stream overloading but did not use it to create project-specific code
std::ostream& operator<<(std::ostream& os, const Item& item);

#endif