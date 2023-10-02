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

    Item (std::string nme, std::string desc, int cals, float wgt);
};

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif