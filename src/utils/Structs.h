#pragma once

#include "Constants.h"
#include "Enums.h"

struct Point {
    int16_t x;
    int16_t y;
};

struct Rect {
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;
};

struct TitleScreenVars {

    uint8_t delay = 0;
    uint8_t charIndex = 0;
    uint8_t frameIndex = 0;
    TitleScreenSettingsMode mode = TitleScreenSettingsMode::Language;
    
    void reset() {

        // this->cursor = Language::English;

    }

};

struct StatisticsScreenVars {

    StatisticsMode mode = StatisticsMode::PageOne;
    uint8_t numberOfAttempts = 0;
    
    void reset() {

        this->mode = StatisticsMode::PageOne;

    }

};

struct KeyboardVars {

    uint8_t xCursor = 0;
    uint8_t yCursor = 0;
    uint8_t yPos = 57;

    KeyboardState state;
    KeyState keys[26];

    void reset() {

        for (uint8_t i = 0; i < 26; i++) {
            keys[i] = KeyState::Visible;
        }

    }

};

struct GuessesVar {

    char chars[6][5];
    GuessState state[6][5];
    uint8_t xCursor = 0;
    uint8_t yCursor = 0;
    int8_t listY = 0;

    void reset() {

        for (uint8_t y = 0; y < 6; y++) {

            for (uint8_t x = 0; x < 5; x++) {
                this->chars[y][x] = ' ';
                this->state[y][x] = GuessState::Dashed;
            }

        }

        this->xCursor = 0;
        this->yCursor = 0;
        this->listY = 0;

    }

};

struct GamePlayVars {

    Language language = Language::English;
    GameMode gameMode = GameMode::Single;
    KeyboardVars keyboard;
    GuessesVar guesses;

    uint8_t showInvalidWord_Count = 0;
    CheckState checkState = CheckState::Normal;
    uint8_t cancelButton = 0;
    int8_t holes[9];
    int8_t holesTotal;

    #ifdef USE_BRINE
    char selectedWord[5] = { 'B', 'R', 'I', 'N', 'E' };
    #else
    char selectedWord[5] = { ' ', ' ', ' ', ' ', ' ' };
    #endif

    void reset() {

        for (uint8_t i = 0; i < 9; i++) {

            this->holes[i] = 0;

        }

        this->holesTotal = 0;

    }

};

struct SplashScreenVars {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};