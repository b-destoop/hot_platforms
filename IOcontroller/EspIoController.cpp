//
// Created by bert on 14/07/24.
//

#include <cstdint>
#include "EspIoController.h"


#include "driver/gpio.h"

#include "pinouts.h"


void EspIoController::update() {

}

uint8_t EspIoController::get_buttons() {
    // get all the player ports

    // compare the ports to the previously known version of the ports

    // store the difference between the current and previous state if needed

    // save the current ports as the prev state

    // return the difference
    return 0;
}

EspIoController::EspIoController() {
    for (gpio_num_t button: buttons) {
        gpio_set_direction(button, GPIO_MODE_INPUT);
        gpio_set_pull_mode(button, GPIO_PULLDOWN_ONLY);
    }
}
