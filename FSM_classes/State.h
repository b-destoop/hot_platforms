//
// Created by bert on 18/06/24.
//

#ifndef FSM_OOP_STATE_H
#define FSM_OOP_STATE_H

#include <list>
#include "../TStateTypes.h"

#include "Transition.h"

class FSM;


class State {
private:
    FSM *fsm;
    TState state;
    std::list<Transition *> transitions;
public:
    explicit State(TState state, FSM *fsm) : fsm(fsm), state(state) {}

    void addTransition(State *destination, bool(FSM::*condition)()); // from, to, condition, fsm

    TState getState() { return state; };

    State *update() {
        for (Transition *t: transitions) {
            if (t->check_condition())
                return t->get_to_state();
        }
        return this;
    };

};


#endif //FSM_OOP_STATE_H
