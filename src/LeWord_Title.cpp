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

    if (PC::buttons.pressed(BTN_UP)) {

        switch (this->titleScreenVars.mode) {

            case TitleScreenSettingsMode::Language:

                if (this->gamePlayVars.language == Language::French) {
                    
                    this->gamePlayVars.language = Language::English; 
                    this->cookie->setMode(this->gamePlayVars.language, this->gamePlayVars.gameMode);

                }

                break;
            
            case TitleScreenSettingsMode::GameMode:

                if (this->gamePlayVars.gameMode == GameMode::NineHole) {
                    
                    this->gamePlayVars.gameMode = GameMode::Single; 
                    this->cookie->setMode(this->gamePlayVars.language, this->gamePlayVars.gameMode);

                }

                break;

        }

    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        switch (this->titleScreenVars.mode) {

            case TitleScreenSettingsMode::Language:

                if (this->gamePlayVars.language == Language::English) {
                    
                    this->gamePlayVars.language = Language::French; 
                    this->cookie->setMode(this->gamePlayVars.language, this->gamePlayVars.gameMode);

                }

                break;
            
            case TitleScreenSettingsMode::GameMode:

                if (this->gamePlayVars.gameMode == GameMode::Single) {
                    
                    this->gamePlayVars.gameMode = GameMode::NineHole; 
                    this->cookie->setMode(this->gamePlayVars.language, this->gamePlayVars.gameMode);

                }

                break;

        }

    }
    
    if (PC::buttons.pressed(BTN_LEFT) && titleScreenVars.mode == TitleScreenSettingsMode::GameMode) {
        
        this->titleScreenVars.mode = TitleScreenSettingsMode::Language;

    }
    
    if (PC::buttons.pressed(BTN_RIGHT) && titleScreenVars.mode == TitleScreenSettingsMode::Language) {
        
        this->titleScreenVars.mode = TitleScreenSettingsMode::GameMode;

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

    PD::setColor(12);
    PD::fillRect(0, 0, 110, 50);
    PD::setColor(3);
    PD::fillRect(0, 50, 110, 38);
    PD::drawBitmap(0, 30, Images::Background);


    PD::drawBitmap(5, 11, Images::TitleScreen_L[indexes[0]]);
    PD::drawBitmap(22, 11, Images::TitleScreen_E[indexes[1]]);
    PD::drawBitmap(39, 11, Images::TitleScreen_W[indexes[2]]);
    PD::drawBitmap(56, 11, Images::TitleScreen_O[indexes[3]]);
    PD::drawBitmap(73, 11, Images::TitleScreen_R[indexes[4]]);
    PD::drawBitmap(90, 11, Images::TitleScreen_D[indexes[5]]);

    PD::drawBitmap(0, 62, Images::TitleScreen_Lower);


    switch (this->titleScreenVars.mode) {

        case TitleScreenSettingsMode::Language:

            PD::drawBitmap(5, this->gamePlayVars.language == Language::English ? 62 : 72, Images::Pointer);
            PD::drawBitmap(62, this->gamePlayVars.gameMode == GameMode::Single ? 62 : 72, Images::Pointer_Deselect);

            break;
        
        case TitleScreenSettingsMode::GameMode:

            PD::drawBitmap(5, this->gamePlayVars.language == Language::English ? 62 : 72, Images::Pointer_Deselect);
            PD::drawBitmap(62, this->gamePlayVars.gameMode == GameMode::Single ? 62 : 72, Images::Pointer);

            break;

    }

    if (titleScreenVars.frameIndex > 0) {
    
        titleScreenVars.frameIndex--;
    
        if (titleScreenVars.frameIndex == 0) {

            titleScreenVars.delay = random(32, 200);

        }

    }

}
