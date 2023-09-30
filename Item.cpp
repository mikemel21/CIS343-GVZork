#include <iostream>
#include <string>

class Item {
public:
    std::string name;
    std::string description;
    int calories;
    float weight;

    Item (std::string nme, std::string desc, int cals, float wgt) {
        name = nme;
        description = desc;
        calories = cals;
        weight = wgt;

        // exception handling
        std::string errorMsg;
        try {
            // check if name param is empty; throws exception
            if (name.empty())
                throw "Name is empty.";
            if (calories < 0)
                throw "Calories cannot be less than 0.";
            if (calories > 1000)
                throw "Calories cannot be more than 1000.";
            if (description.empty())
                throw "Description cannot be empty.";
            if (weight < 0)
                throw "Weight must be at least 0.";
            if (weight > 500)
                throw "Weight cannot be greater than 500";
        }
        catch (std::string& msg) {
            std::cout << "Exception occurred: " << msg << std::endl;
        }
    }
    //private:
};