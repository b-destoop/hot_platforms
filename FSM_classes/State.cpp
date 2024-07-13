//
// Created by bert on 18/06/24.
//
#include "State.h"

#include <utility>
#include <esp_log.h>
#include "FSM.h"
#include "Transition.h"

const char *tag_s = "STATE";

State::State(TState state, FSM *fsm) : fsm(fsm), state(state) {}

void State::addTransition(State *destination, std::function<bool()> condition) {
    auto *t = new Transition{this, destination, this->fsm, std::move(condition)};
    transitions.push_back(t);
}


void State::setEntryFunction(const std::function<void()> &entryFunction) {
    entry_function = entryFunction;
}

void State::setExitFunction(const std::function<void()> &exitFunction) {
    exit_function = exitFunction;
}

void State::setUpdateFunction(const std::function<void()> &updateFunction) {
    update_function = updateFunction;
}

void State::exitState() {
    if (this->exit_function == nullptr) {
        return;
    }
    this->exit_function();
}

void State::enterState() {
    if (this->entry_function == nullptr) {
        return;
    }
    this->entry_function();
}

