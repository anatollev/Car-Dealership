#include "MenuCustomer.h"
#include <iostream>
#include <limits>

MenuCustomer::MenuCustomer(Shop* shop) : Menu(shop) {}

void MenuCustomer::customer_menu() {
    while (true) {
        draw_header();
        std::cout << "CUSTOMER\n"
            << "=========\n"
            << "1. View available cars\n"
            << "2. View my cars\n"
            << "3. Back to main menu\n"
            << "---------\n"
            << "Select option: ";

        int choice;
        if (!get_valid_input(choice, 1, 3)) {
            pause_and_clear();
            continue;
        }

        switch (choice) {
        case 1:
            car_list_for_customer();
            break;
        case 2:
            customer_cars();
            break;
        case 3:
            return;
        }
    }
}

void MenuCustomer::car_list_for_customer() {
    while (true) {
        draw_header();
        show_car_list(carshop->get_cars());
        std::cout << "=========\n"
            << "Enter car number to buy (or '99' to go back): ";

        int choice;
        if (!get_valid_input(choice, 1, 99)) {
            pause_and_clear();
            continue;
        }

        if (choice == 99) {
            return;
        }

        if (choice <= static_cast<int>(carshop->get_cars().size())) {
            carshop->sell_car(choice);
            carshop->save_car_list_to_file();
            std::cout << "Car purchased successfully\n";
        }
        else {
            std::cout << "Invalid car number\n";
        }
        pause_and_clear();
    }
}

void MenuCustomer::customer_cars() {
    draw_header();
    show_car_list(carshop->get_user().get_cars());
    std::cout << "=========\n"
        << "Press Enter to go back...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}