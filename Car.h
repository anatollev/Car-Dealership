#pragma once
#include "Vehicle.h"
#include <string>

class Car : public Vehicle {
public:
    Car();
    Car(const std::string& new_brand, const std::string& new_model,
        const std::string& new_year, const std::string& new_color,
        int new_power, double new_price);
};