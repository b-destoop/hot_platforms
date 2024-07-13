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

    void update() {
        State *new_state = currState->update();
        if (new_state != currState) {
            currState->exitState();
            currState = new_state;
            currState->enterState();
        }
    };

    void print_state() {
        ESP_LOGI(tag_fsm, "current state: %i", static_cast<int>(currState->getState()));
    }
};


#endif //FSM_OOP_FSM_H
