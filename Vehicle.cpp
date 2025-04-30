#include "Vehicle.h"
#include <sstream>
#include <iomanip>

Vehicle::Vehicle() = default;

Vehicle::Vehicle(const std::string& new_brand, const std::string& new_model,
    const std::string& new_year, const std::string& new_color,
    int new_power, double new_price)
    : brand(new_brand)
    , model(new_model)
    , year(new_year)
    , color(new_color)
    , power(new_power)
    , price(new_price) {
}

std::string Vehicle::get_full_spec(bool for_file, char delim) const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;
    std::string str_price = ss.str();

    if (for_file) {
        return brand + delim + model + delim + year + delim + color + delim +
            std::to_string(power) + delim + str_price + delim;
    }
    return brand + " " + model + " " + year + " " + color + " /" +
        std::to_string(power) + "/ [" + str_price + "]";
}

double Vehicle::get_price() const { return price; }