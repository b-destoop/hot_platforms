//
// Created by bert on 17/06/24.
//

#ifndef HOT_PLATFORMS_GAME_H
#define HOT_PLATFORMS_GAME_H

#include "settings.h"

class Game {
protected:
    Settings &settings;
public:
    explicit Game(Settings &settings) : settings(settings) {}

    virtual int update() { return 0; };
};

#endif //HOT_PLATFORMS_GAME_H
