#include "LeWord.h"
#include "Pokitto.h"
#include "images/Images.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

void Game::statistics_Init() {

    gameState = GameState::Stats;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::statistics() { 

    uint16_t gamesWon = 0;
    uint16_t gamesPlayed = 0;
    uint16_t currentStreak = 0;
    uint16_t maxStreak = 0;
    uint16_t percent = 0;

    if (gamePlayVars.mode == GameMode::English) {

        gamesWon = this->cookie->gamesWon_EN;
        gamesPlayed = this->cookie->gamesPlayed_EN;
        currentStreak = this->cookie->currentStreak_EN;
        maxStreak = this->cookie->maxStreak_EN;

    }
    else {

        gamesWon = this->cookie->gamesWon_FR;
        gamesPlayed = this->cookie->gamesPlayed_FR;
        currentStreak = this->cookie->currentStreak_FR;
        maxStreak = this->cookie->maxStreak_FR;

    }

    percent = (gamesPlayed == 0 ? 0 : (gamesWon * 100) / gamesPlayed);

    if (PC::buttons.pressed(BTN_A)) {
        
        gameState = GameState::Title_Init; 

    }



    // Press B to reset ..

    if (PC::buttons.repeat(BTN_B, 1)) {

        gamePlayVars.cancelButton++;

        if (gamePlayVars.cancelButton == 64) {
            this->cookie->initialise(gamePlayVars.mode);
        }

    }
    else {

        gamePlayVars.cancelButton = false;

    }

    if (gamePlayVars.mode == GameMode::English) {
        PD::drawBitmap(-9, 0, Images::Statistics_EN);
    }
    else {
        PD::drawBitmap(-9, 0, Images::Statistics_FR);
    }

    PD::setColor(12);
    PD::setCursor(20, 14);
    if (gamesPlayed < 100) { PD::print("0"); }
    if (gamesPlayed < 10)  { PD::print("0"); }
    PD::print(gamesPlayed);

    PD::setCursor(73, 14);
    if (percent < 100) { PD::print("0"); }
    if (percent < 10)  { PD::print("0"); }
    PD::print(percent);

    PD::setCursor(20, 39);
    if (currentStreak < 100) { PD::print("0"); }
    if (currentStreak < 10)  { PD::print("0"); }
    PD::print(currentStreak);

    PD::setCursor(73, 39);
    if (maxStreak < 100) { PD::print("0"); }
    if (maxStreak < 10)  {PD::print("0"); }
    PD::print(maxStreak);

}
