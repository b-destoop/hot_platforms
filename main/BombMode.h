//
// Created by bert on 17/06/24.
//

#ifndef HOT_PLATFORMS_BOMBMODE_H
#define HOT_PLATFORMS_BOMBMODE_H

#include "../../../../.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/cstdint"
#include "../FSM_classes/FSM.h"
#include "../FSM_classes/State.h"
#include "settings.h"

class BombMode : public FSM {
private:
    Settings *settings;

    // SWITCH CONDITIONS
    bool init_to_auto_gen_hotpl();

    bool init_to_user_input_add_hot_plates();

    bool auto_gen_hotpl_to_game_ready();

public:
    uint8_t hotplates = 0b0;

    explicit BombMode(Settings *settings);

    ~BombMode() override;

    int count_hot_plates();

    void gen_hot_plates();

};


#endif //HOT_PLATFORMS_BOMBMODE_H
