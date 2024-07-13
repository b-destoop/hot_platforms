#include <cstdio>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <chrono>
#include <thread>
#include "../IOcontroller/PcIOController.h"
#include "../settings.h"
#include "BombMode.h"

#include "soc/soc.h"

#include "driver/gpio.h"

#include "pinouts.h"

gpio_num_t buttons[] = {P1_BUTTON, P2_BUTTON, P3_BUTTON,
                        P4_BUTTON, P5_BUTTON, P6_BUTTON,
                        P7_BUTTON, P8_BUTTON, ACT_BUTTON};

void setup() {
    for (gpio_num_t button: buttons) {
        gpio_set_direction(button, GPIO_MODE_INPUT);
        gpio_set_pull_mode(button, GPIO_PULLDOWN_ONLY);
    }
}

extern "C" void app_main(void) {
    PcIOController ioController;
    Settings settings;
    InPut input;

    BombMode *game = new BombMode(&settings);

    setup();

    // manipulate settings
//    settings.auto_gen_hotplate = false;

    while (true) {
        vTaskDelay(10);


        game->print_state();
        game->update();

    }

    delete game;
}
