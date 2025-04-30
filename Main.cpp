#include "Menu.h"
#include "Shop.h"

int main() {
    Shop carshop("UA Mega Cars", "1st Street, 24, Kyiv", "123-433-556", "9843", 0.0);
    Menu menu(&carshop);
    menu.user_choose();
    return 0;
}