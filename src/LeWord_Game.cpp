
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

<<<<<<< Updated upstream
        switch (this->gamePlayVars.language) {
=======
        switch (this->gamePlayVars.mode) {
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
        switch (this->gamePlayVars.language) {
=======
        switch (this->gamePlayVars.mode) {
>>>>>>> Stashed changes

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


<<<<<<< Updated upstream
        this->gamePlayVars.cancelButton++;

        if (this->gamePlayVars.cancelButton == 64) {
            this->gamePlayVars.checkState = CheckState::Quit;
        }

    }
    else {

        this->gamePlayVars.cancelButton = false;
=======
    // Pause?

    if (PC::buttons.released(BTN_C)) {

        this->gameState = GameState::Pause_Init;
>>>>>>> Stashed changes

    }


    switch (this->gamePlayVars.checkState) {

        case CheckState::InvalidWord:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
                this->gamePlayVars.checkState = CheckState::Normal;
            }
            break;

        case CheckState::CorrectWord:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
<<<<<<< Updated upstream
                this->cookie->increaseCorrectWords(this->gamePlayVars.language, this->gamePlayVars.guesses.yCursor);
=======
                this->cookie->increaseCorrectWords(this->gamePlayVars.mode, this->gamePlayVars.guesses.yCursor);
>>>>>>> Stashed changes
                this->statisticsScreenVars.numberOfAttempts = this->gamePlayVars.guesses.yCursor + 1;
                this->gameState = GameState::Stats_Init;
            }
            break;

        case CheckState::TooManyAttempts:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
<<<<<<< Updated upstream
                this->cookie->resetWiningStreak(this->gamePlayVars.language);
=======
                this->cookie->resetWiningStreak(this->gamePlayVars.mode);
>>>>>>> Stashed changes
                this->gameState = GameState::Stats_Init;
            }
            break;

        case CheckState::Quit:
            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
<<<<<<< Updated upstream
                if (this->gamePlayVars.guesses.yCursor > 0) this->cookie->resetWiningStreak(this->gamePlayVars.language);
=======
                if (this->gamePlayVars.guesses.yCursor > 0) this->cookie->resetWiningStreak(this->gamePlayVars.mode);
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
                        if (this->gamePlayVars.guesses.listY > Constants::scroll_Limits[this->gamePlayVars.guesses.yCursor]) {
=======
                        if (this->gamePlayVars.guesses.listY > Constants::Scroll_Limits[this->gamePlayVars.guesses.yCursor]) {
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
                                        this->gamePlayVars.guesses.listY = -((this->gamePlayVars.guesses.yCursor - 3) * Constants::guess_Spacing);
=======
                                        this->gamePlayVars.guesses.listY = -((this->gamePlayVars.guesses.yCursor - 3) * Constants::Guess_Spacing);
>>>>>>> Stashed changes
                                    }

                                }
                                break;

                            default: break;

                        }

                    }

                }
                else {
                    
<<<<<<< Updated upstream
                    //if (keyboard[Constants::key_Map[this->gamePlayVars.keyboard.yCursor][this->gamePlayVars.keyboard.xCursor]] != KeyState::Invisible) {

                        if (this->gamePlayVars.guesses.xCursor < 5) {

                            this->gamePlayVars.guesses.chars[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = 65 + Constants::key_Map[this->gamePlayVars.keyboard.yCursor][this->gamePlayVars.keyboard.xCursor];
=======
                    //if (keyboard[Constants::Key_Map[this->gamePlayVars.keyboard.yCursor][this->gamePlayVars.keyboard.xCursor]] != KeyState::Invisible) {

                        if (this->gamePlayVars.guesses.xCursor < 5) {

                            this->gamePlayVars.guesses.chars[this->gamePlayVars.guesses.yCursor][this->gamePlayVars.guesses.xCursor] = 65 + Constants::Key_Map[this->gamePlayVars.keyboard.yCursor][this->gamePlayVars.keyboard.xCursor];
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
    drawMan(tmpManX, tmpManB, tmpManI, tmpManP, tmpManK);
    drawGuesses(tmpManK, this->gamePlayVars.guesses.listY);

    switch (this->gamePlayVars.checkState) {

        case CheckState::InvalidWord:
            if (this->gamePlayVars.language == Language::English) {
=======
    this->renderScreen();



    // Housekeeping ..

    if (this->gamePlayVars.showInvalidWord_Count > 0 && PC::frameCount % 2 == 0) this->gamePlayVars.showInvalidWord_Count--;

}


void Game::renderScreen() {

    drawGuesses(this->gamePlayVars.guesses.listY);

    switch (this->gamePlayVars.checkState) {

        case CheckState::InvalidWord:
            if (this->gamePlayVars.mode == GameMode::English) {
>>>>>>> Stashed changes
                PD::drawBitmap(14, 72, Images::InvalidWord_EN);
            }
            else {
                PD::drawBitmap(-4, 72, Images::InvalidWord_FR);
            }
            break;

        case CheckState::CorrectWord:
<<<<<<< Updated upstream
            if (this->gamePlayVars.language == Language::English) {
=======
            if (this->gamePlayVars.mode == GameMode::English) {
>>>>>>> Stashed changes
                PD::drawBitmap(32, 72, Images::Correct_EN);
            }
            else {
                PD::drawBitmap(32, 27, Images::Correct_FR);
            }
            break;

        case CheckState::TooManyAttempts:
            drawSolution();
<<<<<<< Updated upstream
            if (this->gamePlayVars.language == Language::English) {
=======
            if (this->gamePlayVars.mode == GameMode::English) {
>>>>>>> Stashed changes
                PD::drawBitmap(9, 61, Images::TooManyAttempts_EN);
            }
            else {
                PD::drawBitmap(1, 61, Images::TooManyAttempts_FR);
            }
            break;

        case CheckState::Quit:
            PD::setColor(0);
            PD::fillRect(0, 59, 128, 3);
<<<<<<< Updated upstream
            if (this->gamePlayVars.language == Language::English) {
=======
            if (this->gamePlayVars.mode == GameMode::English) {
>>>>>>> Stashed changes
                PD::drawBitmap(20, 61, Images::Quit_EN);
            }
            else {
                PD::drawBitmap(23, 61, Images::Quit_FR);
            }
            drawSolution();
            break;

        default:
<<<<<<< Updated upstream
            drawKeyboard(10 + tmpManK, this->gamePlayVars.keyboard.yPos);
=======
            drawKeyboard(10, this->gamePlayVars.keyboard.yPos);
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream


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

=======
>>>>>>> Stashed changes
}

void Game::drawSolution() {

    // Render words ..

    PD::setColor(0);

    for (uint8_t x = 0; x < 5; x++) {

        PD::setColor(3, 7);
        PD::fillRect(Constants::Guess_Left + (x * Constants::Guess_Spacing), 72, Constants::Guess_Spacing - 2, Constants::Guess_Spacing - 2);
        PD::setColor(7, 3);
<<<<<<< Updated upstream
        PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 1, 74);
=======
        PD::setCursor(Constants::Guess_Left + (x * Constants::Guess_Spacing) + 1, 74);
>>>>>>> Stashed changes
        PD::print(this->gamePlayVars.selectedWord[x]);

    }

    PD::setColor(7, 0);

}


void Game::drawGuesses(int8_t yOffset) {

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
                    PD::fillRect(Constants::Guess_Left + (x * Constants::Guess_Spacing) + xMove, y * Constants::Guess_Spacing + yOffset + yMove[x], Constants::Guess_Spacing - 2, Constants::Guess_Spacing - 2);
                    PD::setColor(7, 3);
<<<<<<< Updated upstream
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
=======
                    PD::setCursor(Constants::Guess_Left + (x * Constants::Guess_Spacing) + 3 + xMove - 2, y * Constants::Guess_Spacing + 2 + yOffset + yMove[x]);
>>>>>>> Stashed changes
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    break;

                case GuessState::WrongPosition:
                    PD::setColor(9, 7);
                    PD::fillRect(Constants::Guess_Left + (x * Constants::Guess_Spacing) + xMove, y * Constants::Guess_Spacing + yOffset + yMove[x], Constants::Guess_Spacing - 2, Constants::Guess_Spacing - 2);
                    PD::setColor(7, 9);
<<<<<<< Updated upstream
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
=======
                    PD::setCursor(Constants::Guess_Left + (x * Constants::Guess_Spacing) + 3 + xMove - 2, y * Constants::Guess_Spacing + 2 + yOffset + yMove[x]);
>>>>>>> Stashed changes
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    break;

                case GuessState::Dashed:
                    PD::setColor(7, 0);
<<<<<<< Updated upstream
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
=======
                    PD::setCursor(Constants::Guess_Left + (x * Constants::Guess_Spacing) + 3 + xMove - 2, y * Constants::Guess_Spacing + 2 + yOffset + yMove[x]);
>>>>>>> Stashed changes
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    PD::setColor(5, 0);
                    PD::drawFastHLine(Constants::Guess_Left + (x * Constants::Guess_Spacing) + xMove, ((y + 1) * Constants::Guess_Spacing) - 2 + yOffset + yMove[x], Constants::Guess_Spacing - 2);
                    break;


                default:
                    PD::setColor(5, 7);
                    PD::fillRect(Constants::Guess_Left + (x * Constants::Guess_Spacing) + xMove, y * Constants::Guess_Spacing + yOffset + yMove[x], Constants::Guess_Spacing - 2, Constants::Guess_Spacing - 2);
                    PD::setColor(7, 5);
<<<<<<< Updated upstream
                    PD::setCursor(Constants::guess_Left + (x * Constants::guess_Spacing) + 3 + xMove + xOffset - 2, y * Constants::guess_Spacing + 2 + yOffset + yMove[x]);
=======
                    PD::setCursor(Constants::Guess_Left + (x * Constants::Guess_Spacing) + 3 + xMove - 2, y * Constants::Guess_Spacing + 2 + yOffset + yMove[x]);
>>>>>>> Stashed changes
                    PD::print(this->gamePlayVars.guesses.chars[y][x]);
                    break;

            }

        }

        PD::setColor(7, 0);

    }

}
