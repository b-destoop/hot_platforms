//
// Created by bert on 10/06/24.
//

#ifndef HOT_PLATFORMS_PCIOCONTROLLER_H
#define HOT_PLATFORMS_PCIOCONTROLLER_H

#include "IOController.h"
#include <map>
#include <curses.h>

class PcIOController : IOController {
private:
    std::string line1;
    std::string line2;

public:
    void cout_line1(std::string output) override {
        line1 = output;
        std::cout << line1 << std::endl;
        std::cout << line2 << std::endl;
    }

    void cout_line2(std::string output) override {
        line2 = output;
        std::cout << line1 << std::endl;
        std::cout << line2 << std::endl;
    }

    InPut cin() override {
        int ch;

        initscr();
        noecho();
        cbreak();	/* Line buffering disabled. pass on everything */
        ch = getch();

//        switch (ch) {
//            case
//        }
        return InPut::p1;

    }
};


#endif //HOT_PLATFORMS_PCIOCONTROLLER_H
