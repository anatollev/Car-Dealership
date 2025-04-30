#include "Shop.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Shop::Shop() : user(nullptr), profit(0.0) {}

Shop::Shop(const std::string& new_title, const std::string& new_address,
    const std::string& new_tel, const std::string& pin, double new_profit)
    : user(nullptr)
    , title(new_title)
    , address(new_address)
    , telephone(new_tel)
    , admin_pin(pin)
    , profit(new_profit) {
    load_car_list_from_file();
    load_profit_from_file();
}

Shop::~Shop() = default;

User Shop::get_user() const {
    return user ? *user : User("customer");
}

std::string Shop::get_title() const { return title; }
std::string Shop::get_addr() const { return address; }
std::string Shop::get_tel() const { return telephone; }

std::string Shop::get_profit() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << profit;
    return ss.str();
}

void Shop::set_user(User* usr) { user = usr; }

bool Shop::check_admin_pin(const std::string& pin) const {
    return pin == admin_pin;
}

std::list<Car> Shop::get_cars() const { return garage; }

void Shop::add_car(const std::string& brand, const std::string& model,
    const std::string& year, const std::string& color,
    int power, double price) {
    garage.emplace_back(brand, model, year, color, power, price);
}

void Shop::add_car_from_array(const std::array<std::string, 6>& car_data) {
    try {
        int power = std::stoi(car_data[4]);
        double price = std::stod(car_data[5]);
        add_car(car_data[0], car_data[1], car_data[2], car_data[3], power, price);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing car data: " << e.what() << "\n";
    }
}

void Shop::remove_car(int index) {
    if (index <= 0) return;

    auto it = garage.begin();
    std::advance(it, index - 1);
    if (it != garage.end()) {
        garage.erase(it);
    }
}

void Shop::sell_car(int index) {
    if (index <= 0 || !user) return;

    auto it = garage.begin();
    std::advance(it, index - 1);
    if (it != garage.end()) {
        profit += it->get_price();
        user->buy_car(*it);
        garage.erase(it);
        save_profit_to_file();
    }
}

void Shop::save_car_list_to_file() const {
    std::ofstream file(garage_file_name, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open cars file for writing\n";
        return;
    }

    for (const auto& car : garage) {
        file << car.get_full_spec(true, delim) << "\n";
    }
}

void Shop::load_car_list_from_file() {
    std::ifstream file(garage_file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open cars file for reading\n";
        return;
    }

    std::array<std::string, 6> car_data;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        size_t index = 0;
        std::string token;
        while (std::getline(iss, token, delim) && index < car_data.size()) {
            car_data[index++] = token;
        }
        if (index == 6) {
            add_car_from_array(car_data);
        }
    }
}

void Shop::save_profit_to_file() const {
    std::ofstream file(profit_file_name, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open profit file for writing\n";
        return;
    }
    file << std::fixed << std::setprecision(2) << profit;
}

void Shop::load_profit_from_file() {
    std::ifstream file(profit_file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open profit file for reading\n";
        return;
    }

    std::string line;
    if (std::getline(file, line) && !line.empty()) {
        try {
            profit = std::stod(line);
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing profit: " << e.what() << "\n";
        }
    }
}