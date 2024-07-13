//
// Created by bert on 18/06/24.
//

#ifndef FSM_OOP_STATE_H
#define FSM_OOP_STATE_H

#include <list>
#include "TStateTypes.h"

#include "Transition.h"

class FSM;


class State {
private:
    FSM *fsm;
    TState state;
    std::list<Transition *> transitions;
    std::function<void()> entry_function, exit_function, update_function;
public:
    State(TState state, FSM *fsm);

    /**
     * Method to call when the state becomes active.
     * aka "entering" the state
     */
    void enterState();

    /**
     * Method to call when the state becomes inactive.
     * aka "exiting" the state
     */
    void exitState();

    void setEntryFunction(const std::function<void()> &entryFunction);

    void setExitFunction(const std::function<void()> &exitFunction);

    void setUpdateFunction(const std::function<void()> &updateFunction);

    void addTransition(State *destination, std::function<bool()> condition);

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
