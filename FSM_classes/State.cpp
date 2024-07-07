//
// Created by bert on 18/06/24.
//
#include "State.h"

#include <utility>
#include "FSM.h"
#include "Transition.h"

void State::addTransition(State *destination, std::function<bool()> condition) {
    auto *t = new Transition{this, destination, this->fsm, std::move(condition)};
    transitions.push_back(t);
}

