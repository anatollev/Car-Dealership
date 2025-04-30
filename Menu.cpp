#include "Menu.h"
#include "MenuAdmin.h"
#include "MenuCustomer.h"
#include <iostream>
#include <limits>
#include <algorithm>

Menu::Menu(Shop* shop) : carshop(shop) {}

void Menu::clear_screen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI clear screen
}

void Menu::draw_header() {
    clear_screen();
    std::cout << "\n" << carshop->get_title() << "\n"
        << "================\n"
        << "CAR SHOP\n"
        << "================\n"
        << "Address: " << carshop->get_addr() << "\n"
        << "Phone: " << carshop->get_tel() << "\n\n";
}

void Menu::user_choose() {
    while (true) {
        draw_header();
        std::cout << "USER ROLE\n"
            << "=========\n"
            << "1. Customer\n"
            << "2. Administrator\n"
            << "3. Exit\n"
            << "---------\n"
            << "Select option: ";

        int choice;
        if (!get_valid_input(choice, 1, 3)) {
            pause_and_clear();
            continue;
        }

        switch (choice) {
        case 1: {
            User user("customer");
            carshop->set_user(&user);
            MenuCustomer customer(carshop);
            customer.customer_menu();
            break;
        }
        case 2: {
            User user("admin");
            if (enter_admin_pin(&user)) {
                carshop->set_user(&user);
                MenuAdmin admin(carshop);
                admin.admin_menu();
            }
            break;
        }
        case 3:
            return;
        }
    }
}

bool Menu::enter_admin_pin(User* user) {
    draw_header();
    std::cout << "ENTER ADMIN PIN (or '0' to go back)\n"
        << "=========\n";

    std::string pin;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "PIN: ";
        std::getline(std::cin, pin);
        trim(pin);

        if (pin == "0") {
            return false;
        }
        if (carshop->check_admin_pin(pin)) {
            return true;
        }
        std::cout << "Wrong PIN, try again\n";
        pause_and_clear();
    }
}

void Menu::show_car_list(const std::list<Car>& cars) {
    if (cars.empty()) {
        std::cout << "No cars available\n";
        return;
    }

    int index = 0;
    for (const auto& car : cars) {
        std::cout << ++index << ". " << car.get_full_spec(false) << "\n";
    }
    std::cout << "\n";
}

bool Menu::get_valid_input(int& choice, int min, int max) {
    std::string input;
    std::getline(std::cin, input);
    trim(input);

    try {
        size_t pos;
        choice = std::stoi(input, &pos);
        if (pos != input.length() || choice < min || choice > max) {
            throw std::out_of_range("Invalid range");
        }
        return true;
    }
    catch (...) {
        std::cout << "Please enter a number between " << min << " and " << max << "\n";
        return false;
    }
}

void Menu::pause_and_clear() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clear_screen();
}

void Menu::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), str.end());
}