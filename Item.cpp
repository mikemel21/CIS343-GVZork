#include "Item.hpp"
#include <stdexcept>
Item::Item (std::string name, std::string description, int calories, float weight) {
    this->name = name;
    this->description = description;
    this->calories = calories;
    this->weight = weight;

    // exception handling
    if (name.empty())
        throw std::invalid_argument("Name is empty.");
    if (calories < 0)
        throw std::invalid_argument("Calories cannot be less than 0.");
    if (calories > 1000)
        throw std::invalid_argument("Calories cannot be more than 1000.");
    if (description.empty())
        throw std::invalid_argument("Description cannot be empty.");
    if (weight < 0)
        throw std::invalid_argument("Weight must be at least 0.");
    if (weight > 500)
        throw std::invalid_argument("Weight cannot be greater than 500");


    // std::string errorMsg;
    // try {
    //     // check if name param is empty; throws exception
    //     if (name.empty())
    //         throw "Name is empty.";
    //     if (calories < 0)
    //         throw "Calories cannot be less than 0.";
    //     if (calories > 1000)
    //         throw "Calories cannot be more than 1000.";
    //     if (description.empty())
    //         throw "Description cannot be empty.";
    //     if (weight < 0)
    //         throw "Weight must be at least 0.";
    //     if (weight > 500)
    //         throw "Weight cannot be greater than 500";
    // }
    // catch (std::string& msg) {
    //     std::cout << "Exception occurred: " << msg << std::endl;
    // }
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (" << item.calories << " calories) - " << item.weight << " lb(s) - " << item.description;
    return os;
}