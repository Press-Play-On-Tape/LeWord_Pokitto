#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
#include "utils/Structs.h"
//#include "src/sounds/Sounds.h"
#include "utils/SFXVolumeSource.hpp"
#include "dictionary/Dictionary.h"
#include "animations/Animations.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;

class Game {

    private:
        TitleScreenVars titleScreenVars;
        SplashScreenVars splashScreenVars;
        GamePlayVars gamePlayVars;
        GameState gameState = GameState::SplashScreen_Init;
        GameCookie *cookie;

        uint16_t man_delay = random(Constants::Delay_Low, Constants::Delay_High);
        uint8_t man_Idx = 0;
        AnimationSequence animation = AnimationSequence::Walk_RL;
        File file;

    public:
        void setup(GameCookie *cookie);
        void loop();

    private:
        void splashScreen_Init();
        void splashScreen();
        void game_Init();
        void game();
        void drawSolution();
        void drawGuesses(int8_t xOffset, int8_t yOffset);
        void drawMan(uint8_t tmpManX, uint8_t tmpManB, uint8_t tmpManI, uint8_t tmpManP, int8_t tmpManK);
        void drawKeyboard(uint8_t xOffset, uint8_t yOffset);
        void statistics_Init();
        void statistics(); 
        void title_Init();
        void title(); 
        void moveCursor(Direction direction);
        CheckState checkWord();
};

