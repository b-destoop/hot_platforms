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

    Game *game = new BombMode(settings);
    auto *game_as_bm = dynamic_cast<BombMode *>(game);

//    while(true){
//        std::this_thread::sleep_for(std::chrono::milliseconds(300));
//        game->update();
//    }

    for (int i = 0; i < 30; i++) {
        game_as_bm->gen_hot_plates();
        std::bitset<8> x(game_as_bm->hotplates);
        std::cout << "hot plates: " << x << std::endl;
        int nr = game_as_bm->count_hot_plates();
        std::cout << "count: " << nr << std::endl;
    }
    std::cout << "nr o hotplates: " << game_as_bm->count_hot_plates() << std::endl;

    delete game;
    return 0;
}
