#include "LeWord.h"
#include "Pokitto.h"
#include "images/Images.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::splashScreen_Init() {

    splashScreenVars.counter = 0;
    gameState = GameState::SplashScreen;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::splashScreen() { 

    if (PC::buttons.repeat(BTN_A))  { this->gameState = GameState::Title_Init; }


    auto justPressed = PC::buttons.repeat(BTN_A) || PC::buttons.repeat(BTN_B) || PC::buttons.repeat(BTN_C);

    if (justPressed > 0) {

        this->gameState = GameState::Title_Init; 

    }
    
    if (PC::frameCount % 12 == 0) {
     
        splashScreenVars.counter++;
        
        if (splashScreenVars.counter == 4) {
            
            splashScreenVars.counter = 0;
            
        }
        
    }
   

    PD::drawBitmap(22, 27, Images::Ppot_Full);
    PD::drawBitmap(32, 38, Images::Ppot[splashScreenVars.counter]);

    if (splashScreenVars.counter < 2) PD::drawBitmap(81, 36, Images::Ppot_Arrow);

}
