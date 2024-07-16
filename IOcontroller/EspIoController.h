//
// Created by bert on 14/07/24.
//

#ifndef HOTPLATES_ESPIOCONTROLLER_H
#define HOTPLATES_ESPIOCONTROLLER_H

#include <cstdint>

typedef uint16_t io_state;

class EspIoController {
private:
    /**
     * bit: |15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
     * btn: |  |  |  |  |  |  |  |at|p8|p7|p6|p5|p4|p3|p2|p1|
     */
    io_state buttons_curr = 0, buttons_last = 0; // represent the players from right to left

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
     * Returns the buttons that were pressed at the last update() loop
     * @return 8 bits showing which player platforms were registered to have been pressed
     */
    uint8_t get_buttons();
};


#endif //HOTPLATES_ESPIOCONTROLLER_H
