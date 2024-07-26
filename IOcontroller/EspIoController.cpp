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


io_state EspIoController::get_io_downs() {
    /**
     * last btns =  0000    0010    0010
     * curr btns =  0010    0000    0100
     * result =     0010    0000    0100
     *
     * algorithm: (NOT(last buttons)) AND (curr buttons)
     */
    io_state io_down = (~this->io_last) & (this->io_curr);
    return io_down;
}

io_state EspIoController::get_io_ups() {
    /**
     * last btns =  0010    0110    0001
     * curr btns =  0000    0100    0101
     * result =     0010    0010    0000
     *
     * algorithm = (last buttons) AND (NOT(curr buttons))
     */
    io_state io_up = (this->io_last) & (~this->io_curr);
    return io_up;
}


pltfrm_state EspIoController::get_platform_downs() {
    // take the least significant bits of io_state --> these contain the platforms
    pltfrm_state downs = this->get_io_downs();
    return downs;
}

pltfrm_state EspIoController::get_platform_ups() {
    // take the least significant bits of io_state --> these contain the platforms
    pltfrm_state ups = this->get_io_ups();
    return ups;
}

pltfrm_state EspIoController::get_btns_state(io_state ioState) {
    return (pltfrm_state) ioState;
}

bool EspIoController::get_activate_down() {
    io_state downs = get_io_downs();
    return downs >> 8;
}

void EspIoController::play_pos_tritone() {
    // todo: make speaker work
    ESP_LOGI(tag_io, "~positive tritone plays~");
}

void EspIoController::play_buzzer() {
    // todo: make speaker work
    ESP_LOGI(tag_io, "~buzzer plays~");
}

void EspIoController::servo_aim(pltfrm_state player) {
    // todo: implement servo aim. Make this->servo_aimed thread safe
    ESP_LOGI(tag_io, "aiming servo");
    this->servo_aimed = true;
}

bool EspIoController::isServoAimed() {
    bool aimed = this->servo_aimed;
    if (aimed) this->servo_aimed = false;
    return aimed;
}

void EspIoController::servo_fire() {
    // todo: implement servo fire
    ESP_LOGI(tag_io, "firing servo");
    this->servo_fired = true;
}

bool EspIoController::isServoFired() {
    bool fired = this->servo_fired;
    if (fired) this->servo_fired = false;
    return fired;
}



