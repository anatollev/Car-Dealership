#pragma once
#include "Menu.h"

class MenuAdmin : public Menu {
public:
    MenuAdmin(Shop* shop);

    void admin_menu();
    void car_list_for_admin();
    void add_car_form();

private:
    template<typename T>
    bool get_valid_numeric_input(T& value, T min, T max);
};