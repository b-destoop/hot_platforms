//
// Created by bert on 18/06/24.
//

#ifndef FSM_OOP_TRANSITION_H
#define FSM_OOP_TRANSITION_H

#include <functional>
#include <utility>

class State;

class FSM;

class Transition {
private:
    State *from, *to;
    FSM *fsm;

    std::function<bool()> switch_condition;

public:
    Transition(State *from, State *to, FSM *fsm, std::function<bool()> condition) : from(from), to(to), fsm(fsm),
                                                                                    switch_condition(
                                                                                            std::move(condition)) {}

    /**
     * Get the state to transition to
     * @return the state to transition to
     */
    State *get_to_state() { return to; };

    bool check_condition() { return switch_condition(); }; // perform the condition() method from the fsm object
};


#endif //FSM_OOP_TRANSITION_H
