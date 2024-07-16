//
// Created by bert on 14/07/24.
//

#ifndef HOTPLATES_ESPIOCONTROLLER_H
#define HOTPLATES_ESPIOCONTROLLER_H


#include <cstdint>

class EspIoController {
private:
    uint8_t prev_player_state = 0;
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
