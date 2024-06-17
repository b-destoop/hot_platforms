//
// Created by bert on 17/06/24.
//

#ifndef HOT_PLATFORMS_BOMBMODE_H
#define HOT_PLATFORMS_BOMBMODE_H

#include <cstdint>
#include "game.h"

class BombMode : public Game {
    enum BMGameState {
        init,
        auto_generate_hot_plates,
        user_input_add_hot_plates,
        game_ready,
        player_plate_down,
        play_positive_tritone,
        game_over,
        game_over_wait_user_input,
        servo_aim,
        servo_fire
    };
private:
    BMGameState state = init;


public:
    uint8_t hotplates = 0b0;

    explicit BombMode(Settings &settings) : Game(settings) {}

    int update() override;
    int count_hot_plates();
    void gen_hot_plates();

};


#endif //HOT_PLATFORMS_BOMBMODE_H
