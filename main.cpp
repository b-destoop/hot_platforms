#include <iostream>
#include <thread>
#include <bitset>
#include "IOcontroller/IOController.h"
#include "IOcontroller/PcIOController.h"

#include "settings.h"
#include "BombMode.h"

int main() {
    PcIOController ioController;
    Settings settings;
    InPut input;

    BombMode *game = new BombMode(&settings);

    // manipulate settings
//    settings.auto_gen_hotplate = false;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        game->print_state();
        game->update();
    }

    delete game;
    return 0;
}
