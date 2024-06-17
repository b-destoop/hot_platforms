//
// Created by bert on 10/06/24.
//

#ifndef HOT_PLATFORMS_IOCONTROLLER_H
#define HOT_PLATFORMS_IOCONTROLLER_H


#include <string>

enum class InPut {
    up, down, left, right, p1, p2, p3, p4, p5, p6, p7, p8, activate, game_activate
};

class IOController {
public:
    virtual void cout_line1(std::string output) = 0;

    virtual void cout_line2(std::string output) = 0;

    virtual InPut cin() = 0;
};


#endif //HOT_PLATFORMS_IOCONTROLLER_H
