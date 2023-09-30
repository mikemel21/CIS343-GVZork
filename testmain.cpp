#include <iostream>
#include <string>

class Location {
public:
    std::string name;
    std::string description;
    int calories;
    float weight;

    Location (std::string nme, std::string desc, int cals, float wgt) {
        name = nme;
        description = desc;
        calories = cals;
        weight = wgt;

        // exception handling
        std::string errorMsg;
        try {
            // check if name param is empty; throws exception
            if (name.empty())
                throw 0;
            if (calories < 0)
                throw 1;
            if (calories > 1000)
                throw 2;
            if (description.empty())
                throw 3;
            if (weight < 0)
                throw 4;
            if (weight > 500)
                throw 5;
        }
        catch (int msg) {
            if (msg == 0) {
                std::cout << "Exception occurred: Name cannot be empty" << std::endl;
            } else if (msg == 1) {
                std::cout << "Exception occurred: Calories cannot be negative" << std::endl;
            } else if (msg == 2) {
                std::cout << "Exception occurred: Calories cannot be greater than 1000" << std::endl;
            } else if (msg == 3) {
                std::cout << "Exception occurred: Description cannot be empty";
            } else if (msg == 4) {
                std::cout << "Weight cannot be negative" << std::endl;
            } else if (msg == 5) {
                std::cout << "Weight cannot exceed 500";
            }
        }
    }
    //private:
};

int main() {
    Location a("123", "a", 10000, 100);

}