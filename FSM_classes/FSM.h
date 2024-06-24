//
// Created by bert on 18/06/24.
//

#ifndef FSM_OOP_FSM_H
#define FSM_OOP_FSM_H

#include <iostream>
#include <vector>
#include "State.h"


class FSM {
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
            currState = new_state;
        }
    };
};


#endif //FSM_OOP_FSM_H
