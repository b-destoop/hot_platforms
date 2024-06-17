//
// Created by bert on 17/06/24.
//

#ifndef HOT_PLATFORMS_SETTINGS_H
#define HOT_PLATFORMS_SETTINGS_H


class Settings {
public:
    enum GameModes {
        rhythm,
        bomb,
        manual
    };

    GameModes curr_gamemode = bomb;

    // common settings
    bool buzzer_sound = true;

    // bomb mode
    bool trigger_for_fire = true;
    bool auto_gen_hotplate = true;
    int auto_gen_amount = 2;

    // rhythm settings
    bool auto_rhythm = true;
    int auto_rhythm_bpm = 60;
    bool behavior_on_mistake_second_chance = false; // if false, new game when mistaken; if true, try again on mistake
    int auto_rhythm_length = 5;


};


#endif //HOT_PLATFORMS_SETTINGS_H
