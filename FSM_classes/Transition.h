//
// Created by bert on 18/06/24.
//

#ifndef FSM_OOP_TRANSITION_H
#define FSM_OOP_TRANSITION_H

class State;

class FSM;

class Transition {
private:
    State *from, *to;
    FSM *fsm;

    bool (FSM::*condition)();

public:
    Transition(State *from, State *to, FSM *fsm, bool(FSM::*condition)()) : from(from), to(to), fsm(fsm),
                                                                            condition(condition) {};

    State *get_to_state() { return to; };

    bool check_condition() { return (*fsm.*condition)(); }; // perform the condition() method from the fsm object
};


#endif //FSM_OOP_TRANSITION_H
