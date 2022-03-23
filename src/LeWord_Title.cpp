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
        this->sounds.fadeMode = FadeMode::FadeOut;

    }

    if (PC::buttons.pressed(BTN_LEFT)) {
        
        if (titleScreenVars.index == TitleScreenMode::Language) {

            if (this->gamePlayVars.mode == GameMode::French) {
                
                this->gamePlayVars.mode = GameMode::English; 
                this->cookie->setMode(this->gamePlayVars.mode);

            }
    
        }
        else {

            titleScreenVars.index = TitleScreenMode::Language;

        }

    }

    if (PC::buttons.pressed(BTN_RIGHT)) {
        
        if (titleScreenVars.index == TitleScreenMode::Language) {
            
            if (this->gamePlayVars.mode == GameMode::English) {
            
                this->gamePlayVars.mode = GameMode::French; 
                this->cookie->setMode(this->gamePlayVars.mode);

            }
            else {

                titleScreenVars.index = TitleScreenMode::SoundEffects;

            }

        }

    }

    if (PC::buttons.pressed(BTN_B)) {
        
        this->statisticsScreenVars.numberOfAttempts = 7;
        this->gameState = GameState::Stats_Init; 

    }

    if (titleScreenVars.index == TitleScreenMode::SoundEffects && (PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN))) {
        
        if (PC::buttons.pressed(BTN_UP)) {

            this->cookie->sfx--;
            this->cookie->saveCookie();

            if (this->cookie->sfx != SoundSettings::Both && this->cookie->sfx != SoundSettings::Music) {

                this->sounds.muteTheme();
                
            }
            else {

                this->sounds.playTheme(this->cookie->track, this->cookie->sfx);

            }

        }

        if (PC::buttons.pressed(BTN_DOWN)) {

            this->cookie->sfx++;
            this->cookie->saveCookie();

            if (this->cookie->sfx != SoundSettings::Both && this->cookie->sfx != SoundSettings::Music) {

                this->sounds.muteTheme();
                
            }
            else {

                this->sounds.playTheme(this->cookie->track, this->cookie->sfx);
                
            }
            
        }

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

    PD::drawBitmap(5, 26, Images::TitleScreen_L[indexes[0]]);
    PD::drawBitmap(22, 26, Images::TitleScreen_E[indexes[1]]);
    PD::drawBitmap(39, 26, Images::TitleScreen_W[indexes[2]]);
    PD::drawBitmap(56, 26, Images::TitleScreen_O[indexes[3]]);
    PD::drawBitmap(73, 26, Images::TitleScreen_R[indexes[4]]);
    PD::drawBitmap(90, 26, Images::TitleScreen_D[indexes[5]]);

    PD::drawBitmap(0, 57, titleScreenVars.index == TitleScreenMode::Language ? Images::TitleScreen_Lower: Images::TitleScreen_Lower_Inactive);
    PD::drawBitmap(this->gamePlayVars.mode == GameMode::English ? 7 : 65, 57, titleScreenVars.index == TitleScreenMode::Language ? Images::Pointer: Images::Pointer_Inactive);


    switch (this->cookie->sfx) {

        case SoundSettings::Music:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects ? Images::Sound_Music_White: Images::Sound_Music_Inactive);
            break;

        case SoundSettings::SFX:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects ? Images::Sound_SFX_White: Images::Sound_SFX_Inactive);
            break;

        case SoundSettings::Both:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects? Images::Sound_Both_White: Images::Sound_Both_Inactive);
            break;

        default:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects ? Images::Sound_None_White: Images::Sound_None_Inactive);
            break;

    }

    if (titleScreenVars.frameIndex > 0) {
    
        titleScreenVars.frameIndex--;
    
        if (titleScreenVars.frameIndex == 0) {

            titleScreenVars.delay = random(32, 200);

        }

    }

}
