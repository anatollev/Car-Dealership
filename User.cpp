#include "User.h"

User::User(const std::string& user_type) : type(user_type) {}

std::string User::get_user_type() const { return type; }

std::list<Car> User::get_cars() const { return cars; }

void User::buy_car(const Car& car) {
    cars.push_back(car);
}