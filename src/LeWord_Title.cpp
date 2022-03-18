#include "LeWord.h"
#include "Pokitto.h"
#include "images/Images.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

void Game::title_Init() {

    this->gameState = GameState::Title;

    titleScreenVars.delay = random(16, 48);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() { 

    if (PC::buttons.pressed(BTN_A)) {
        
        this->gameState = GameState::Game_Init; 

    }

    if (PC::buttons.pressed(BTN_LEFT) && this->gamePlayVars.language == Language::French) {
        
        this->gamePlayVars.language = Language::English; 
        this->cookie->setMode(this->gamePlayVars.language);

    }

    if (PC::buttons.pressed(BTN_RIGHT) && this->gamePlayVars.language == Language::English) {
        
        this->gamePlayVars.language = Language::French; 
        this->cookie->setMode(this->gamePlayVars.language);

    }

    if (PC::buttons.pressed(BTN_B)) {
        
        this->statisticsScreenVars.numberOfAttempts = 7;
        this->gameState = GameState::Stats_Init; 

    }

    uint8_t indexes[6] = { 0, 0, 0, 0, 0, 0, };

    if (titleScreenVars.delay == 0) {

        indexes[titleScreenVars.charIndex] = titleScreenVars.frameIndex - 1;

    }
    else {

        titleScreenVars.delay--;

        if (titleScreenVars.delay == 0) {

            titleScreenVars.charIndex = random(0, 6);
            titleScreenVars.frameIndex = 19;
            
        }

    }

    PD::drawBitmap(5, 11, Images::TitleScreen_L[indexes[0]]);
    PD::drawBitmap(22, 11, Images::TitleScreen_E[indexes[1]]);
    PD::drawBitmap(39, 11, Images::TitleScreen_W[indexes[2]]);
    PD::drawBitmap(56, 11, Images::TitleScreen_O[indexes[3]]);
    PD::drawBitmap(73, 11, Images::TitleScreen_R[indexes[4]]);
    PD::drawBitmap(90, 11, Images::TitleScreen_D[indexes[5]]);

    PD::drawBitmap(0, 47, Images::TitleScreen_Lower);
    PD::drawBitmap(this->gamePlayVars.language == Language::English ? 7 : 65, 47, Images::Pointer);

    if (titleScreenVars.frameIndex > 0) {
    
        titleScreenVars.frameIndex--;
    
        if (titleScreenVars.frameIndex == 0) {

            titleScreenVars.delay = random(32, 200);

        }

    }

}
