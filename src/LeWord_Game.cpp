
#include "LeWord.h"
#include "Pokitto.h"
#include "images/Images.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


void Game::game_Init() {

    this->gamePlayVars.checkState = CheckState::Normal;
    this->gamePlayVars.cancelButton = 0;
    this->gamePlayVars.keyboard.reset();
    this->gamePlayVars.guesses.reset();

    this->gameState = GameState::Game_Play;

    char status = ' ';
    

    // Pick a random word ..

    #ifndef USE_BRINE

        switch (this->gamePlayVars.language) {

            case Language::English:
                {
                    this->file.openRO("music/LeWord00.img");

                    while (true) {

                        uint32_t word = random(0, Dictionary::English_NumberOfWords) * 6;   
// printf("word : %i\n", word);                        
                        this->file.seek(word);
                        this->file.read(&status, 1);
                        this->file.read(&this->gamePlayVars.selectedWord, 5);

// for (uint8_t i = 0; i < 5; i++) {
// printf("%i ", this->gamePlayVars.selectedWord[i]);
// }        
// printf("\n");

                        if (status == '1') break;

                    }

                }
                break;

            case Language::French:
                {
                    file.openRO("music/LeWord01.img");

                    while (true) {

                        uint32_t word = random(0, Dictionary::French_NumberOfWords) * 6;   
// printf("word : %i\n", word);                        
                        this->file.seek(word);
                        this->file.read(&status, 1);
                        this->file.read(&this->gamePlayVars.selectedWord, 5);

                        if (status == '1') break;

                    }

                    this->file.openRO("/music/LeWord01.img");

                }
                break;

        }                

    #else

        switch (this->gamePlayVars.language) {

            case Language::English:
                this->file.openRO("music/LeWord00.img");
                break;

            case Language::French:
                this->file.openRO("music/LeWord01.img");
                break;

        }                


    #endif

}

void Game::game() {

    uint8_t tmpManX = 0;
    uint8_t tmpManB = 0;
    uint8_t tmpManI = 0;
    uint8_t tmpManP = 0;
    int8_t tmpManK = 0;


    if (man_delay == 0) {

        switch (animation) {

            case AnimationSequence::Think_L:

                tmpManX = Animation::ManData_L[man_Idx * 5];
                tmpManK = Animation::ManData_L[(man_Idx * 5) + 1];
                tmpManB = Animation::ManData_L[(man_Idx * 5) + 2];
                tmpManI = Animation::ManData_L[(man_Idx * 5) + 3];
                tmpManP = Animation::ManData_L[(man_Idx * 5) + 4];
                break;

            case AnimationSequence::Think_R: 
                
                tmpManX = Animation::ManData_R[man_Idx * 5];
                tmpManK = -Animation::ManData_R[(man_Idx * 5) + 1];
                tmpManB = Animation::ManData_R[(man_Idx * 5) + 2];
                tmpManI = Animation::ManData_R[(man_Idx * 5) + 3];
                tmpManP = Animation::ManData_R[(man_Idx * 5) + 4];
                break;

            case AnimationSequence::Walk_LR: 

                tmpManX = man_Idx;
                tmpManK = 0;
                tmpManB = 0;
                tmpManI = ((man_Idx % 6) / 2) + 3;
                tmpManP = 0;
                break;

            case AnimationSequence::Walk_RL: 

                tmpManX = 128 + 16 - man_Idx;
                tmpManK = 0;
                tmpManB = 0;
                tmpManI = ((man_Idx % 6) / 2);
                tmpManP = 0;
                break;

        }

    }


    // Press B to quit ..

    if (PC::buttons.repeat(BTN_B, 1)) {

        this->gamePlayVars.cancelButton++;

        if (this->gamePlayVars.cancelButton == 64) {
            this->gamePlayVars.checkState = CheckState::Quit;
        }

    }
    else {

        this->gamePlayVars.cancelButton = false;

    }


    switch (this->gamePlayVars.checkState) {

        case CheckState::InvalidWord:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
                this->gamePlayVars.checkState = CheckState::Normal;
            }
            break;

        case CheckState::CorrectWord:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
                this->cookie->increaseCorrectWords(this->gamePlayVars.language, this->gamePlayVars.guesses.yCursor);
                this->statisticsScreenVars.numberOfAttempts = this->gamePlayVars.guesses.yCursor + 1;
                this->gameState = GameState::Stats_Init;
            }
            break;

        case CheckState::TooManyAttempts:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
                this->cookie->resetWiningStreak(this->gamePlayVars.language);
                this->gameState = GameState::Stats_Init;
            }
            break;

        case CheckState::Quit:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
                if (this->gamePlayVars.guesses.yCursor > 0) this->cookie->resetWiningStreak(this->gamePlayVars.language);
                this->statisticsScreenVars.numberOfAttempts = 7;
                this->gameState = GameState::Stats_Init;
            }
            break;

        default:

            if (PC::buttons.pressed(BTN_LEFT))   moveCursor(Direction::Left);
            if (PC::buttons.pressed(BTN_RIGHT))  moveCursor(Direction::Right);

            if (PC::buttons.repeat(BTN_UP, 1)) {
                
                switch (this->gamePlayVars.keyboard.state) {

                    case KeyboardState::Showing:
                    case KeyboardState::StartHiding:
                    case KeyboardState::StartShowing:
                        break;

                    default:

                        if (this->gamePlayVars.guesses.listY < 0) {
                            this->gamePlayVars.guesses.listY = this->gamePlayVars.guesses.listY + 1;
                        }
                        break;

                }

            }        

            if (PC::buttons.pressed(BTN_UP)) {
                
                switch (this->gamePlayVars.keyboard.state) {

                    case KeyboardState::Showing:
                        moveCursor(Direction::Up);
                        break;

                    default:
                        break;

                }

            }        

            if (PC::buttons.repeat(BTN_DOWN, 1))   {
                
                switch (this->gamePlayVars.keyboard.state) {

                    case KeyboardState::Showing:
                    case KeyboardState::StartHiding:
                    case KeyboardState::StartShowing:
                        break;

                    default:

                        if (this->gamePlayVars.guesses.listY > Constants::scroll_Limits[this->gamePlayVars.guesses.yCursor]) {
                            this->gamePlayVars.guesses.listY = this->gamePlayVars.guesses.listY - 1;
                        }
                        else{
                            this->gamePlayVars.keyboard.state = KeyboardState::StartShowing;
                        }

                        break;

                }

            }

            if (PC::buttons.pressed(BTN_DOWN))   {
                
                switch (this->gamePlayVars.keyboard.state) {

                    case KeyboardState::Showing:
                        moveCursor(Direction::Down);
                        break;

                    default:
                        break;

                }

            }

            if (PC::buttons.pressed(BTN_B)) {

                if (this->gamePlayVars.guesses.xCursor > 0) {

                    this->gamePlayVars.guesses.xCursor--;
                    this->gamePlayVars.guesses.chars[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = ' ';
                    this->gamePlayVars.guesses.state[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = GuessState::Dashed;

                }

            }

            if (PC::buttons.pressed(BTN_A)) {

                if (this->gamePlayVars.keyboard.xCursor == 0 && this->gamePlayVars.keyboard.yCursor == 2) {

                    if (this->gamePlayVars.guesses.xCursor > 0) {

                        this->gamePlayVars.guesses.xCursor--;
                        this->gamePlayVars.guesses.chars[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = ' ';
                        this->gamePlayVars.guesses.state[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = GuessState::Dashed;

                    }

                }
                else if (this->gamePlayVars.keyboard.xCursor == 8 && this->gamePlayVars.keyboard.yCursor == 2) {

                    // Are there any spaces?

                    bool hasSpace = false;

                    for (uint8_t i = 0; i < 5; i++) {

                        if (this->gamePlayVars.guesses.chars[this->gamePlayVars.guesses.yCursor][i] == ' ') {

                            hasSpace = true;
                            break;

                        }

                    }

                    if (!hasSpace) {

                        this->gamePlayVars.checkState = checkWord();

                        switch (this->gamePlayVars.checkState) {

                            case CheckState::CorrectWord:
                                this->gamePlayVars.showInvalidWord_Count = 19;
                                break;

                            case CheckState::InvalidWord:
                                this->gamePlayVars.showInvalidWord_Count = 15;
                                break;

                            case CheckState::RealWord:

                                if (this->gamePlayVars.guesses.yCursor == 5) {

                                    this->gamePlayVars.checkState = CheckState::TooManyAttempts;

                                }
                                else {
                                    
                                    this->gamePlayVars.guesses.xCursor = 0;
                                    this->gamePlayVars.guesses.yCursor = this->gamePlayVars.guesses.yCursor + 1;

                                    if (this->gamePlayVars.guesses.yCursor >= 4) {
                                        this->gamePlayVars.guesses.listY = -((this->gamePlayVars.guesses.yCursor - 3) * Constants::guess_Spacing);
                                    }

                                }
                                break;

                            default: break;

                        }

                    }

                }
                else {
                    
                    //if (keyboard[Constants::key_Map[this->gamePlayVars.keyboard.yCursor][this->gamePlayVars.keyboard.xCursor]] != KeyState::Invisible) {

                        if (this->gamePlayVars.guesses.xCursor < 5) {

                            this->gamePlayVars.guesses.chars[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = 65 + Constants::key_Map[this->gamePlayVars.keyboard.yCursor][this->gamePlayVars.keyboard.xCursor];

                        }

                        if (this->gamePlayVars.guesses.xCursor < 5) {

                            this->gamePlayVars.guesses.xCursor++;

                            if (this->gamePlayVars.guesses.xCursor == 5) {

                                this->gamePlayVars.keyboard.xCursor = 8;
                                this->gamePlayVars.keyboard.yCursor = 2;

                            }

                        }

                    //}

                }

            }

            break;

    }

    drawMan(tmpManX, tmpManB, tmpManI, tmpManP, tmpManK);
    drawGuesses(tmpManK, this->gamePlayVars.guesses.listY);

    switch (this->gamePlayVars.checkState) {

        case CheckState::InvalidWord:
            if (this->gamePlayVars.language == Language::English) {
                PD::drawBitmap(14, 72, Images::InvalidWord_EN);
            }
            else {
                PD::drawBitmap(-4, 72, Images::InvalidWord_FR);
            }
            break;

        case CheckState::CorrectWord:
            if (this->gamePlayVars.language == Language::English) {
                PD::drawBitmap(32, 72, Images::Correct_EN);
            }
            else {
                PD::drawBitmap(32, 27, Images::Correct_FR);
            }
            break;

        case CheckState::TooManyAttempts:
            drawSolution();
            if (this->gamePlayVars.language == Language::English) {
                PD::drawBitmap(9, 61, Images::TooManyAttempts_EN);
            }
            else {
                PD::drawBitmap(1, 61, Images::TooManyAttempts_FR);
            }
            break;

        case CheckState::Quit:
            PD::setColor(0);
            PD::fillRect(0, 59, 128, 3);
            if (this->gamePlayVars.language == Language::English) {
                PD::drawBitmap(20, 61, Images::Quit_EN);
            }
            else {
                PD::drawBitmap(23, 61, Images::Quit_FR);
            }
            drawSolution();
            break;

        default:
            drawKeyboard(10 + tmpManK, this->gamePlayVars.keyboard.yPos);
            break;

    }


    // Show or hide keyboard ..

    switch (this->gamePlayVars.keyboard.state) {

        case KeyboardState::StartHiding:

            this->gamePlayVars.keyboard.yPos++;
            if (this->gamePlayVars.guesses.yCursor >= 4) this->gamePlayVars.guesses.listY++;

            if (this->gamePlayVars.keyboard.yPos == 88) {
                this->gamePlayVars.keyboard.state = KeyboardState::Hiding;
            }
            break;

        case KeyboardState::StartShowing:

            this->gamePlayVars.keyboard.yPos--;
            if (this->gamePlayVars.guesses.yCursor >= 4) this->gamePlayVars.guesses.listY--;

            if (this->gamePlayVars.keyboard.yPos == 57) {
                this->gamePlayVars.keyboard.state = KeyboardState::Showing;
            }
            break;
        
        default:
            break;
    }



    // Housekeeping ..

    if (this->gamePlayVars.showInvalidWord_Count > 0 && PC::frameCount % 2 == 0) this->gamePlayVars.showInvalidWord_Count--;

    if (PC::frameCount % 3 == 0) {

        if (man_delay > 0) {
            man_delay--;

            if (man_delay == 0) {
                man_Idx = 0;
            }
        }
        else {

            switch (animation) {

                case AnimationSequence::Think_L:

                    man_Idx++;
                    if (man_Idx > 155) {
                        man_delay = random(Constants::Delay_Low, Constants::Delay_High);
                        animation = AnimationSequence::Walk_LR;
                    }

                    break;

                case AnimationSequence::Think_R:

                    man_Idx++;
                    if (man_Idx > 155) {
                        man_delay = random(Constants::Delay_Low, Constants::Delay_High);
                        animation = AnimationSequence::Walk_RL;
                    }

                    break;

                case AnimationSequence::Walk_LR:

                    man_Idx++;
                    if (man_Idx > 128 + 16) {
                        man_delay = random(Constants::Delay_Low, Constants::Delay_High);
                        animation = AnimationSequence::Think_R;
                    }

                    break;

                case AnimationSequence::Walk_RL:

                    man_Idx++;
                    if (man_Idx > 128 + 16) {
                        man_delay = random(Constants::Delay_Low, Constants::Delay_High);
                        animation = AnimationSequence::Think_L;
                    }

                    break;


            }

        }

    }

}


void Game::drawSolution() {

    // Render words ..

    PD::setColor(0);

    for (uint8_t x = 0; x < 5; x++) {

        PD::setColor(3, 7);
        PD::fillRect(Constants::guess_Left + (x * Constants::guess_Spacing), 72, Constants::guess_Spacing - 2, Constants::guess_Spacing - 2);
        PD::setColor(7, 3);
        PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 1, 74);
        PD::print(this->gamePlayVars.selectedWord[x]);

    }

    PD::setColor(7, 0);

}


void Game::drawGuesses(int8_t xOffset, int8_t yOffset) {

    for (uint8_t y = 0; y < this->gamePlayVars.guesses.yCursor + 1; y++) {


        // Animate last row?

        int8_t xMove = 0;
        int8_t yMove[5] = { 0, 0, 0, 0, 0 };
        
        switch (this->gamePlayVars.checkState) {

            case CheckState::InvalidWord:

                if (y == this->gamePlayVars.guesses.yCursor) {
                    if (this->gamePlayVars.showInvalidWord_Count > 0) {
                        xMove = Constants::shake[this->gamePlayVars.showInvalidWord_Count];
                    }
                }
                break;

            case CheckState::CorrectWord:

                if (y == this->gamePlayVars.guesses.yCursor) {

                    if (this->gamePlayVars.showInvalidWord_Count > 0 && this->gamePlayVars.showInvalidWord_Count < 15) yMove[0] = Constants::shake[this->gamePlayVars.showInvalidWord_Count];
                    if (this->gamePlayVars.showInvalidWord_Count > 1 && this->gamePlayVars.showInvalidWord_Count < 16) yMove[1] = Constants::shake[this->gamePlayVars.showInvalidWord_Count - 1];
                    if (this->gamePlayVars.showInvalidWord_Count > 2 && this->gamePlayVars.showInvalidWord_Count < 17) yMove[2] = Constants::shake[this->gamePlayVars.showInvalidWord_Count - 2];
                    if (this->gamePlayVars.showInvalidWord_Count > 3 && this->gamePlayVars.showInvalidWord_Count < 18) yMove[3] = Constants::shake[this->gamePlayVars.showInvalidWord_Count - 3];
                    if (this->gamePlayVars.showInvalidWord_Count > 4 && this->gamePlayVars.showInvalidWord_Count < 19) yMove[4] = Constants::shake[this->gamePlayVars.showInvalidWord_Count - 4];

                }

                break;

            default: break;

        }


        // Render words ..

        for (uint8_t x = 0; x < 5; x++) {

            switch (this->gamePlayVars.guesses.state[y][x]) {

                case GuessState::Correct:
                    PD::setColor(3, 7);
                    PD::fillRect(Constants::guess_Left + (x * Constants::guess_Spacing) + xMove + xOffset, y * Constants::guess_Spacing + yOffset + yMove[x], Constants::guess_Spacing - 2, Constants::guess_Spacing - 2);
                    PD::setColor(7, 3);
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    break;

                case GuessState::WrongPosition:
                    PD::setColor(9, 7);
                    PD::fillRect(Constants::guess_Left + (x * Constants::guess_Spacing) + xMove + xOffset, y * Constants::guess_Spacing + yOffset + yMove[x], Constants::guess_Spacing - 2, Constants::guess_Spacing - 2);
                    PD::setColor(7, 9);
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    break;

                case GuessState::Dashed:
                    PD::setColor(7, 0);
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    PD::setColor(5, 0);
                    PD::drawFastHLine(Constants::guess_Left + (x * Constants::guess_Spacing) + xMove + xOffset, ((y + 1) * Constants::guess_Spacing) - 2 + yOffset + yMove[x], Constants::guess_Spacing - 2);
                    break;


                default:
                    PD::setColor(5, 7);
                    PD::fillRect(Constants::guess_Left + (x * Constants::guess_Spacing) + xMove + xOffset, y * Constants::guess_Spacing + yOffset + yMove[x], Constants::guess_Spacing - 2, Constants::guess_Spacing - 2);
                    PD::setColor(7, 5);
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    break;

            }

        }

        PD::setColor(7, 0);

    }

}


void Game::drawMan(uint8_t tmpManX, uint8_t tmpManB, uint8_t tmpManI, uint8_t tmpManP, int8_t tmpManK) {


    // Draw man?

    if (man_delay == 0) {

        switch (animation) {

            case AnimationSequence::Think_L:

                if (tmpManP > 0) {
                    PD::drawBitmap(2, 28, Images::Man_Word[tmpManP - 1]);
                }

                switch (tmpManB) {

                    case 1:
                        PD::drawBitmap(tmpManX - 16, 36, Images::LightBulb);
                        break;

                }

                PD::drawBitmap(tmpManX - 16, 45, Images::Man[tmpManI]); 
                break;

            case AnimationSequence::Think_R:
                
                if (tmpManP > 0) {
                    PD::drawBitmap(106, 28, Images::Man_Word[tmpManP - 1]);
                }

                switch (tmpManB) {

                    case 1:
                        PD::drawBitmap(136 - tmpManX, 36, Images::LightBulb);
                        break;

                }

                PD::drawBitmap(136 - tmpManX, 45, Images::Man[tmpManI]);
                break;
        
            case AnimationSequence::Walk_LR:
            case AnimationSequence::Walk_RL:
                PD::drawBitmap(tmpManX - 16, 45, Images::Man[tmpManI]); 
                break;

        }

    }

}