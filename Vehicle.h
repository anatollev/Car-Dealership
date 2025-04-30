#pragma once
#include <string>

class Vehicle {
protected:
    std::string brand;
    std::string model;
    std::string year;
    std::string color;
    int power;
    double price;

public:
    Vehicle();
    Vehicle(const std::string& new_brand, const std::string& new_model,
        const std::string& new_year, const std::string& new_color,
        int new_power, double new_price);

    std::string get_full_spec(bool for_file, char delim = ' ') const;
    double get_price() const;
};