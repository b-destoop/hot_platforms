//
// Created by bert on 18/06/24.
//

#ifndef FSM_OOP_FSM_H
#define FSM_OOP_FSM_H

#include <iostream>
#include <vector>
#include <esp_log.h>
#include "State.h"


class FSM {
private:
    const char *tag_fsm = "FSM";
protected:
    State *currState;
    std::vector<State *> states; // keep track to be able to dealloc
public:
    // transition conditions
    // define some state transitions

    virtual ~FSM() {
        delete currState;
        for (State *state: states) {
            delete state;
        }
    }

    /**
     * Update the FSM game loop
     * @return true if the fsm state has changed
     */
    bool update() {
        State *new_state = currState->update();
        if (new_state != currState) {
            currState->exitState();
            currState = new_state;
            currState->enterState();
            return true;
        }
        return false;
    };

    void print_state() {
        std::string msg = "current state: ";
        switch (currState->getState()) {
            case TState::init:
                msg.append("init");
                break;
            case TState::auto_generate_hot_plates:
                msg.append("auto generate hot plates");
                break;
            case TState::user_input_add_hot_plates:
                msg.append("user input add hot plates");
                break;
            case TState::add_p_to_hot_plates:
                msg.append("add #p to hot plates");
                break;
            case TState::game_ready:
                msg.append("game ready");
                break;
            case TState::player_plate_down:
                msg.append("player plate down");
                break;
            case TState::plyr_plate_up_cold:
                msg.append("plyr plate up cold");
                break;
            case TState::plyr_plate_up_hot:
                msg.append("plyr plate up hot");
                break;
            case TState::play_positive_tritone:
                msg.append("player positive tritone");
                break;
            case TState::game_over:
                msg.append("game over");
                break;
            case TState::game_over_wait_user_input:
                msg.append("game over wait user input");
                break;
            case TState::servo_aim:
                msg.append("servo aim");
                break;
            case TState::servo_fire:
                msg.append("servo fire");
                break;
        }
        ESP_LOGI(tag_fsm, "%s", msg.c_str());
    }
};


#endif //FSM_OOP_FSM_H
