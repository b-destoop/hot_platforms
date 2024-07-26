//
// Created by bert on 14/07/24.
//

#ifndef HOTPLATES_ESPIOCONTROLLER_H
#define HOTPLATES_ESPIOCONTROLLER_H

#include <cstdint>

typedef uint16_t io_state;
typedef uint8_t pltfrm_state;

class EspIoController {
private:
    /**
     * bit mapping of buttons:
     * bit: |15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
     * btn: |  |  |  |  |  |  |  |at|p8|p7|p6|p5|p4|p3|p2|p1|
     */
    io_state io_curr = 0, io_last = 0; // represent the players from right to left

    /**
     * returns the buttons part of an ioState.
     * ==> just the 8 least significant bits of an io_state, so just cast from io_state to btns_state
     * @param ioState
     * @return
     */
    static pltfrm_state get_btns_state(io_state ioState);

public:
    /**
     * Configure all the pins of the microcontroller
     */
    explicit EspIoController();

    /**
     * Update all the variables in the controller. This method is supposed to be called once per game loop.
     */
    void update();

    /**
     * returns the gpio inputs that changed state from not on to on at the last update() loop.
     * @return sizeof(io_state) bits that show which states came on
     */
    io_state get_io_downs();

    /**
     * returns the gpio inputs that changed state from on to not on at the last update() loop.
     * @return sizeof(io_state) bits that show which states went off
     */
    io_state get_io_ups();

    /**
     * Returns the buttons (plates) that changed state from not pressed to pressed at the last update() loop.
     * @return 8 bits showing which player platforms were registered to have been pressed
     */
    pltfrm_state get_platform_downs();

    /**
     * Returns the buttons (plates) that changed state from pressed to not pressed at the last update() loop.
     * @return 8 bits showing which player platforms were registered to have been released
     */
    pltfrm_state get_platform_ups();

    /**
     * Checks if the activate button was pressed.
     * @return true if the button was pressed, false in the other case
     */
    bool get_activate_down();

    /**
     * play a positive tritone on the speaker. Meant as a reward
     */
    void play_pos_tritone();
};


#endif //HOTPLATES_ESPIOCONTROLLER_H
