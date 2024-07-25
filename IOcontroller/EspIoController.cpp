//
// Created by bert on 14/07/24.
//

#include <cstdint>
#include <esp_log.h>
#include "EspIoController.h"


#include "driver/gpio.h"

#include "pinouts.h"

const char *tag_io = "IO CTRL";

EspIoController::EspIoController() {
    for (gpio_num_t button: buttons) {
        gpio_set_direction(button, GPIO_MODE_INPUT);
        gpio_set_pull_mode(button, GPIO_PULLDOWN_ONLY);
    }
}

void EspIoController::update() {
    this->io_last = this->io_curr;

    this->io_curr = 0;
    for (int i = 0; i < buttons.size(); i++) {
        uint16_t level = gpio_get_level(buttons[i]);
        this->io_curr |= (level << i);
    }
}

btns_state EspIoController::get_button_downs() {
    /**
     * last btns =  0000    0010    0010
     * curr btns =  0010    0000    0100
     * result =     0010    0000    0100
     *
     * algorithm: (NOT(last buttons)) AND (curr buttons)
     */
    btns_state last_buttons = get_btns_state(this->io_last);
    btns_state curr_buttons = get_btns_state(this->io_curr);
    btns_state buttons_down = (~last_buttons) & curr_buttons;
    return buttons_down;
}

btns_state EspIoController::get_btns_state(io_state ioState) {
    return (btns_state) ioState;
}
