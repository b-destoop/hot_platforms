//
// Created by bert on 17/06/24.
//

#include "BombMode.h"
#include <iostream>
#include <esp_log.h>
#include <esp_random.h>

#define DEBUG(MSG) std::cout << "BM - " << MSG << std::endl;

// ------------------ HELPER FUNCTIONS ------------------

const char *tag_bm = "BOMBMODE";

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

unsigned int BombMode::count_hot_plates() {
    return count_bits(this->hotplates);
}

/**
 * Generates the hot plates based on the number set int settings.
 * This method assumes 8 players and an 8 bit int based on this amount of players.
 */
void BombMode::gen_hot_plates() {
    uint8_t new_hp = 0;
    while (count_bits(new_hp) != this->settings->auto_gen_amount) {
        // shift the number until the last bit is not 1
        while (new_hp & 1)
            new_hp <<= 1;

        // make the last bit 1
        new_hp |= 1;

        // shift a random amount
        new_hp <<= esp_random() % 7;
    }
    this->hotplates = new_hp;
}

// ------------------ CONSTR/DESTR ------------------
BombMode::BombMode(Settings *settings) : settings(settings) {
    auto *init = new State(TState::init, this);
    auto auto_gen_hotpl = new State(TState::auto_generate_hot_plates, this);
    auto user_input_add_hot_plates = new State(TState::user_input_add_hot_plates, this);
    auto game_ready = new State(TState::game_ready, this);
    auto player_plate_down = new State(TState::player_plate_down, this);
    auto play_pos_trt = new State(TState::play_positive_tritone, this);
    auto game_over = new State(TState::game_over, this);
    auto game_over_wait_user_input = new State(TState::game_over_wait_user_input, this);
    auto servo_aim = new State(TState::servo_aim, this);
    auto servo_fire = new State(TState::servo_fire, this);

    init->addTransition(auto_gen_hotpl, [this] { return this->init_to_auto_gen_hotpl(); });
    init->addTransition(user_input_add_hot_plates, [this] { return this->init_to_user_input_add_hot_plates(); });

    auto_gen_hotpl->addTransition(game_ready, [this] { return this->auto_gen_hotpl_to_game_ready(); });


    states.push_back(init);
    states.push_back(auto_gen_hotpl);
    states.push_back(user_input_add_hot_plates);
    states.push_back(game_ready);
    states.push_back(player_plate_down);
    states.push_back(play_pos_trt);
    states.push_back(game_over);
    states.push_back(game_over_wait_user_input);
    states.push_back(servo_aim);
    states.push_back(servo_fire);

    currState = init;
    init->enterState();
}

BombMode::~BombMode() {
    for (State *state: states) {
        delete state;
    }
}

// SWITCH CONDITIONS
bool BombMode::init_to_auto_gen_hotpl() {
    return settings->auto_gen_hotplate;
}

bool BombMode::init_to_user_input_add_hot_plates() {
    return !settings->auto_gen_hotplate;
}

bool BombMode::auto_gen_hotpl_to_game_ready() {
    gen_hot_plates();
    ESP_LOGI(tag_bm, "amount of generated plates: %d, coordinates: %d", this->count_hot_plates(), this->hotplates);
    return true;
}

