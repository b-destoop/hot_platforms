//
// Created by bert on 17/06/24.
//

#ifndef HOT_PLATFORMS_BOMBMODE_H
#define HOT_PLATFORMS_BOMBMODE_H

#include "../../../../.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/cstdint"
#include "../FSM_classes/FSM.h"
#include "../FSM_classes/State.h"
#include "settings.h"
#include "../IOcontroller/EspIoController.h"

class BombMode : public FSM {
private:
    Settings *settings;
    EspIoController *ioController;

    // SWITCH CONDITIONS

public:
    pltfrm_state hotplates = 0b0;

    explicit BombMode(Settings *settings, EspIoController *ioController);

    ~BombMode() override;

    unsigned int count_hot_plates();

    void gen_hot_plates();

};


#endif //HOT_PLATFORMS_BOMBMODE_H
