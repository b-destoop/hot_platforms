#include <cstdio>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <chrono>
#include <thread>
#include "../IOcontroller/PcIOController.h"
#include "settings.h"
#include "BombMode.h"

#include "soc/soc.h"

extern "C" void app_main(void) {
    Settings settings;

    auto ioController = new EspIoController;

    auto game = new BombMode(&settings, ioController);

    // manipulate settings
//    settings.auto_gen_hotplate = false;

    while (true) {
        vTaskDelay(10);

        ioController->update();

        if (game->update()) {
            game->print_state();
        }

    }

    delete game;
}
