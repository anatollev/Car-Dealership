#pragma once
#include "Shop.h"
#include "User.h"
#include <list>
#include <string>

class Menu {
protected:
    Shop* carshop;

    void clear_screen();
    void pause_and_clear();
    void trim(std::string& str);
    bool get_valid_input(int& choice, int min, int max);

public:
    Menu(Shop* shop);
    virtual ~Menu() = default;

    void draw_header();
    void user_choose();
    bool enter_admin_pin(User* user);
    void show_car_list(const std::list<Car>& cars);
};