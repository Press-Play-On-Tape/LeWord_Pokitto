#include "LeWord.h"
#include "Pokitto.h"
#include "images/Images.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;
//    this->sounds.connectVolumeControl(1);

}

void Game::loop() {

    PC::buttons.pollButtons();
    PD::clear();

    switch (this->gameState) {

        case GameState::SplashScreen_Init:

            splashScreen_Init();
            [[fallthrough]]

        case GameState::SplashScreen:

            splashScreen();
            break;

        case GameState::Title_Init:

            // sounds.playTheme(2, this->cookie->sfx, true, true);
            title_Init();
            this-> gameState = GameState::Title;
            [[fallthrough]]

        case GameState::Title:

            title();
            break;

        case GameState::Game_Init:

            game_Init();
            this-> gameState = GameState::Game_Play;
            [[fallthrough]]

        case GameState::Game_Play:

            game();
            break;

        case GameState::Stats_Init:

            statistics_Init();
            [[fallthrough]]

        case GameState::Stats:

            statistics();
            break;

    }

}