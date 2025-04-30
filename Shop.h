#pragma once
#include "Car.h"
#include "User.h"
#include <string>
#include <list>
#include <array>

class Shop {
private:
    User* user;
    std::list<Car> garage;
    std::string title;
    std::string address;
    std::string telephone;
    double profit;
    std::string admin_pin;
    const std::string garage_file_name = "cars.txt";
    const std::string profit_file_name = "profit.txt";
    const char delim = '^';

public:
    Shop();
    Shop(const std::string& new_title, const std::string& new_address,
        const std::string& new_tel, const std::string& pin, double new_profit);
    ~Shop();

    User get_user() const;
    std::string get_title() const;
    std::string get_addr() const;
    std::string get_tel() const;
    std::string get_profit() const;

    void set_user(User* usr);
    bool check_admin_pin(const std::string& pin) const;
    std::list<Car> get_cars() const;

    void add_car(const std::string& brand, const std::string& model,
        const std::string& year, const std::string& color,
        int power, double price);
    void add_car_from_array(const std::array<std::string, 6>& car_data);
    void remove_car(int index);
    void sell_car(int index);

    void save_car_list_to_file() const;
    void load_car_list_from_file();
    void save_profit_to_file() const;
    void load_profit_from_file();
};