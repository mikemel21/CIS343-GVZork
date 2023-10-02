#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>

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
std::ostream& operator<<(std::ostream& os, const Item& item);

#endif