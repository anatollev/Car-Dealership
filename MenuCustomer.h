#pragma once
#include "Menu.h"

class MenuCustomer : public Menu {
public:
    MenuCustomer(Shop* shop);

    void customer_menu();
    void car_list_for_customer();
    void customer_cars();
};