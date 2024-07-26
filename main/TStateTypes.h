//
// Created by bert on 23/06/24.
//

#ifndef HOT_PLATFORMS_TSTATETYPES_H
#define HOT_PLATFORMS_TSTATETYPES_H

/**
 * define names for all the possible states
 */
enum class TState {
    init,
    auto_generate_hot_plates,
    user_input_add_hot_plates,
    add_p_to_hot_plates,
    game_ready,
    player_plate_down,
    plyr_plate_up_cold,
    plyr_plate_up_hot,
    play_positive_tritone,
    play_buzzer,
    game_over,
    game_over_wait_user_input,
    servo_aim,
    servo_fire,
};

#endif //HOT_PLATFORMS_TSTATETYPES_H
