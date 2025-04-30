#pragma once
#include "Car.h"
#include <string>
#include <list>

class User {
private:
    std::list<Car> cars;
    std::string type;

public:
    User(const std::string& user_type);

    std::string get_user_type() const;
    std::list<Car> get_cars() const;
    void buy_car(const Car& car);
};