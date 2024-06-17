#include <iostream>
#include "IOcontroller/IOController.h"
#include "IOcontroller/PcIOController.h"

int main() {
    PcIOController ioController;
    InPut input;

    ioController.cout_line1("this is supposed to be on line 1");
    ioController.cout_line2("select gamemode >");

    ioController.cin();

//    std::cout << "select a gamemode" << std::endl;
//    std::getline(std::cin, selection);
//
//    std::cout << selection;

    return 0;
}
