//
// Created by bert on 18/06/24.
//
#include "State.h"
#include "FSM.h"
#include "Transition.h"

void State::addTransition(State *destination, bool (FSM::*condition)()) {
    auto *t = new Transition{this, destination, this->fsm, condition};
    transitions.push_back(t);
}
