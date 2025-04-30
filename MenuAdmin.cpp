#include "MenuAdmin.h"
#include <iostream>
#include <limits>

MenuAdmin::MenuAdmin(Shop* shop) : Menu(shop) {}

void MenuAdmin::admin_menu() {
    while (true) {
        draw_header();
        std::cout << "ADMINISTRATOR [Profit: " << carshop->get_profit() << "]\n"
            << "=========\n"
            << "1. View car list\n"
            << "2. Add car\n"
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
            car_list_for_admin();
            break;
        case 2:
            add_car_form();
            break;
        case 3:
            return;
        }
    }
}

void MenuAdmin::car_list_for_admin() {
    while (true) {
        draw_header();
        show_car_list(carshop->get_cars());
        std::cout << "=========\n"
            << "Enter car number to remove (or '99' to go back): ";

        int choice;
        if (!get_valid_input(choice, 1, 99)) {
            pause_and_clear();
            continue;
        }

        if (choice == 99) {
            return;
        }

        if (choice <= static_cast<int>(carshop->get_cars().size())) {
            carshop->remove_car(choice);
            carshop->save_car_list_to_file();
            std::cout << "Car removed successfully\n";
        }
        else {
            std::cout << "Invalid car number\n";
        }
        pause_and_clear();
    }
}

void MenuAdmin::add_car_form() {
    draw_header();
    std::string brand, model, year, color;
    int power;
    double price;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter car details:\n";
    std::cout << "Brand: ";
    std::getline(std::cin, brand);
    trim(brand);

    std::cout << "Model: ";
    std::getline(std::cin, model);
    trim(model);

    std::cout << "Year: ";
    std::getline(std::cin, year);
    trim(year);

    std::cout << "Color: ";
    std::getline(std::cin, color);
    trim(color);

    std::cout << "Power (HP): ";
    while (!get_valid_numeric_input(power, 1, 2000)) {
        std::cout << "Please enter a valid power (1-2000): ";
    }

    std::cout << "Price: ";
    while (!get_valid_numeric_input(price, 0.0, 10000000.0)) {
        std::cout << "Please enter a valid price (0-10000000): ";
    }

    if (brand.empty() || model.empty() || year.empty() || color.empty()) {
        std::cout << "All fields must be filled\n";
        pause_and_clear();
        return;
    }

    carshop->add_car(brand, model, year, color, power, price);
    carshop->save_car_list_to_file();
    std::cout << "\n=========\n"
        << "SUCCESS: Car added to shop\n";
    pause_and_clear();
}

template<typename T>
bool MenuAdmin::get_valid_numeric_input(T& value, T min, T max) {
    std::string input;
    std::getline(std::cin, input);
    trim(input);

    try {
        size_t pos;
        if constexpr (std::is_integral_v<T>) {
            value = std::stoi(input, &pos);
        }
        else {
            value = std::stod(input, &pos);
        }
        if (pos != input.length() || value < min || value > max) {
            throw std::out_of_range("Invalid range");
        }
        return true;
    }
    catch (...) {
        return false;
    }
}