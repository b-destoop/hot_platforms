//
// Created by bert on 12/07/24.
//

#ifndef HOTPLATES_PINOUTS_H
#define HOTPLATES_PINOUTS_H

#include "driver/gpio.h"

#include <vector>

#define P1_BUTTON GPIO_NUM_26
#define P2_BUTTON GPIO_NUM_25
#define P3_BUTTON GPIO_NUM_34 // has no internal pulldown
#define P4_BUTTON GPIO_NUM_27
#define P5_BUTTON GPIO_NUM_33
#define P6_BUTTON GPIO_NUM_32
#define P7_BUTTON GPIO_NUM_39 // has no internal pulldown
#define P8_BUTTON GPIO_NUM_22

#define ACT_BUTTON GPIO_NUM_23


static const std::vector<gpio_num_t> buttons =
        {P1_BUTTON, P2_BUTTON, P3_BUTTON,
         P4_BUTTON, P5_BUTTON, P6_BUTTON,
         P7_BUTTON, P8_BUTTON, ACT_BUTTON}; // order matter for io controller

static const std::vector<gpio_num_t> player_buttons =
        {P1_BUTTON, P2_BUTTON, P3_BUTTON,
         P4_BUTTON, P5_BUTTON, P6_BUTTON,
         P7_BUTTON, P8_BUTTON};

#endif //HOTPLATES_PINOUTS_H
