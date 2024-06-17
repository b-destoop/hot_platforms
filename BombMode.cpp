//
// Created by bert on 17/06/24.
//

#include "BombMode.h"
#include <iostream>

#define DEBUG(MSG) std::cout << "BM - " << MSG << std::endl;

int BombMode::update() {
    BMGameState next_state = init;
    switch (this->state) {
        case init:
            DEBUG("current state init")
            // inputs
            if (this->settings.auto_gen_hotplate) {
                next_state = auto_generate_hot_plates;
            } else {
                next_state = user_input_add_hot_plates;
            }
            // outputs
            break;
        case auto_generate_hot_plates:
            DEBUG("current state autogen hotplates")
            // inputs
            // none

            // outputs
            gen_hot_plates();



            // todo: generate the hot plates
            // if hot plates generation is done
            next_state = game_ready;
            break;
        case user_input_add_hot_plates:
            DEBUG("current state user input hot plates")
            // inputs

            // outputs

            // todo
            // if latest input = platform nr x
            // add platform to hot plates
            // if latest intput = activate
            // next state
            break;
        case game_ready:
            DEBUG("current state game ready")
            // inputs

            // outputs
            break;
        case player_plate_down:
            break;
        case play_positive_tritone:
            break;
        case game_over:
            break;
        case game_over_wait_user_input:
            break;
        case servo_aim:
            break;
        case servo_fire:
            break;
    }
    this->state = next_state;
}

/**
 * Algorithm can be found here
 * https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 * @return
 */
unsigned int count_bits(int n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int BombMode::count_hot_plates() {
    return count_bits(this->hotplates);
}

/**
 * Generates the hot plates based on the number set int settings.
 * This method assumes 8 players and an 8 bit int based on this amount of players.
 * todo: randomly seed the auto generator: https://en.cppreference.com/w/cpp/numeric/random/rand
 */
void BombMode::gen_hot_plates() {
    uint8_t new_hp = 0;
    while (count_bits(new_hp) != this->settings.auto_gen_amount) {
        // shift the number until the last bit is not 1
        while (new_hp & 1)
            new_hp <<= 1;

        // make the last bit 1
        new_hp |= 1;

        // shift a random amount
        new_hp <<= rand() % 7;
    }
    this->hotplates = new_hp;
}


