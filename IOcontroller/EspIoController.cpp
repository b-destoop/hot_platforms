//
// Created by bert on 14/07/24.
//

#include <cstdint>
#include <esp_log.h>
#include "EspIoController.h"


#include "driver/gpio.h"

#include "pinouts.h"

const char* tag_io = "IO CTRL";

EspIoController::EspIoController() {
    for (gpio_num_t button: buttons) {
        gpio_set_direction(button, GPIO_MODE_INPUT);
        gpio_set_pull_mode(button, GPIO_PULLDOWN_ONLY);
    }
}

void EspIoController::update() {
    this->buttons_last = this->buttons_curr;

    this->buttons_curr = 0;
    for (int i = 0; i < buttons.size(); i++) {
        uint16_t level = gpio_get_level(buttons[i]);
        this->buttons_curr |= (level << i);
    }

    ESP_LOGI(tag_io, "buttons curr: %d", this->buttons_curr);
}

uint8_t EspIoController::get_buttons() {
    // get all the player ports

    // compare the ports to the previously known version of the ports

    // store the difference between the current and previous state if needed

    // save the current ports as the prev state

    // return the difference
    return 0;
}

