#include "Car.h"

Car::Car() = default;

Car::Car(const std::string& new_brand, const std::string& new_model,
    const std::string& new_year, const std::string& new_color,
    int new_power, double new_price)
    : Vehicle(new_brand, new_model, new_year, new_color, new_power, new_price) {
}