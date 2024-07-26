//
// Created by bert on 17/06/24.
//

#include "BombMode.h"
#include <iostream>
#include <esp_log.h>
#include <esp_random.h>

#include "../IOcontroller/EspIoController.h"

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
BombMode::BombMode(Settings *settings, EspIoController *ioController) : settings(settings), ioController{ioController} {
    auto init = new State(TState::init, this);
    auto auto_gen_hotpl = new State(TState::auto_generate_hot_plates, this);
    auto user_input = new State(TState::user_input_add_hot_plates, this);
    auto add_p_to_hot_plates = new State(TState::add_p_to_hot_plates, this);

    auto game_ready = new State(TState::game_ready, this);
    auto player_plate_down = new State(TState::player_plate_down, this);
    auto platform_up_cold = new State(TState::plyr_plate_up_cold, this);
    auto platform_up_hot = new State(TState::plyr_plate_up_hot, this);
    auto play_pos_trt = new State(TState::play_positive_tritone, this);

    auto game_over = new State(TState::game_over, this);
    auto game_over_wait_user_input = new State(TState::game_over_wait_user_input, this);
    auto servo_aim = new State(TState::servo_aim, this);
    auto servo_fire = new State(TState::servo_fire, this);

    init->addTransition(auto_gen_hotpl, [this] {
        return this->settings->auto_gen_hotplate;
    });

    init->addTransition(user_input, [this] {
        return !this->settings->auto_gen_hotplate;
    });

    auto_gen_hotpl->addTransition(game_ready, [this] {
        gen_hot_plates();
        ESP_LOGI(tag_bm, "amount of generated plates: %d, coordinates: %d", this->count_hot_plates(), this->hotplates);
        return true;
    });

    user_input->addTransition(add_p_to_hot_plates, [this] {
        pltfrm_state buttons = this->ioController->get_platform_downs();
        if (buttons) {
            ESP_LOGI(tag_bm, "buttons were pressed %u", buttons);
            return true;
        }
        return false;
    });
    add_p_to_hot_plates->setEntryFunction([this] {
        // xor works like switch
        this->hotplates = this->hotplates ^ this->ioController->get_platform_downs();
        ESP_LOGI(tag_bm, "hot plates: %u", this->hotplates);
    });

    add_p_to_hot_plates->addTransition(user_input, [] {
        // immediately return to the user_input state, hotplates are updated on state entry
        return true;
    });

    user_input->addTransition(game_ready, [this] {
        bool foo = this->ioController->get_activate_down();
        if (foo) {
            ESP_LOGI(tag_bm, "activate pressed");
        }
        return foo;
    });

    game_ready->addTransition(player_plate_down, [this] {
        pltfrm_state downs = this->ioController->get_platform_downs();
        if (downs) ESP_LOGI(tag_bm, "platform downs: %u", downs);
        return downs;
    });

    player_plate_down->addTransition(platform_up_cold, [this] {
        // check for ups
        pltfrm_state ups = this->ioController->get_platform_ups();
        if (ups) ESP_LOGI(tag_bm, "platform ups: %u", ups);

        // check that the ups are cold
        return ups & ~this->hotplates;
    });

    player_plate_down->addTransition(platform_up_hot, [this] {
        // check for ups
        pltfrm_state ups = this->ioController->get_platform_ups();
        if (ups) ESP_LOGI(tag_bm, "platform ups: %u", ups);

        // check that the ups are hot
        return ups & this->hotplates;
    });

    platform_up_cold->addTransition(game_ready, [this] {
        /* note: this implementation of an FSM makes this boolean check happen
         * twice instead of once with different outcomes depending on the result
         * --> not super-duper efficient */
        return !this->settings->buzzer_sound;
    });

    platform_up_cold->addTransition(play_pos_trt, [this] {
        return this->settings->buzzer_sound;
    });

    play_pos_trt->setEntryFunction([this] {
        this->ioController->play_pos_tritone();
    });

    play_pos_trt->addTransition(game_ready, [] {
        return true;
    });


    states.push_back(init);
    states.push_back(auto_gen_hotpl);
    states.push_back(user_input);
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

