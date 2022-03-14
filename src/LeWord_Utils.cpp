#include "LeWord.h"
#include "Pokitto.h"
#include "images/Images.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

void Game::moveCursor(Direction direction) {

    switch (direction) {

        case Direction::Right:
    
            switch (gamePlayVars.keyboard.yCursor) {

                case 0:
                    if (gamePlayVars.keyboard.xCursor < 9) {
                        
                        gamePlayVars.keyboard.xCursor++;

                    }
                    else {

                        gamePlayVars.keyboard.xCursor = 0;

                    }
                    break;

                case 1:
                case 2:
                    if (gamePlayVars.keyboard.xCursor < 8) {
                        
                        gamePlayVars.keyboard.xCursor++;

                    }
                    else {

                        gamePlayVars.keyboard.xCursor = 0;

                    }
                    break;

            }

            break;

        case Direction::Left:
    
            switch (gamePlayVars.keyboard.yCursor) {

                case 0:
                    if (gamePlayVars.keyboard.xCursor > 0) {

                        gamePlayVars.keyboard.xCursor--;

                    }
                    else {

                        gamePlayVars.keyboard.xCursor = 9;

                    }

                    break;

                case 1:
                case 2:
                    if (gamePlayVars.keyboard.xCursor > 0) {

                        gamePlayVars.keyboard.xCursor--;

                    }
                    else {

                        gamePlayVars.keyboard.xCursor = 8;

                    }

                    break;

            }
             
            break;

        case Direction::Down:
    
            switch (gamePlayVars.keyboard.yCursor) {

                case 0:
                    if (gamePlayVars.keyboard.xCursor == 9) {
                        
                        gamePlayVars.keyboard.yCursor++;
                        gamePlayVars.keyboard.xCursor--;

                    }
                    else {
                        gamePlayVars.keyboard.yCursor++;
                    }
                    break;

                case 1:
                    gamePlayVars.keyboard.yCursor++;
                    break;

            }

            break;

        case Direction::Up:
    
            if (gamePlayVars.keyboard.yCursor == 0) {

                gamePlayVars.keyboard.state = KeyboardState::StartHiding;
                break;

            }
            else {

                switch (gamePlayVars.keyboard.yCursor) {

                    case 0:
                    case 2:
                        if (gamePlayVars.keyboard.xCursor == 9) {
                            gamePlayVars.keyboard.yCursor--;
                            gamePlayVars.keyboard.xCursor--;
                        }
                        else {
                            gamePlayVars.keyboard.yCursor--;
                        }
                        break;

                    case 1:
                        gamePlayVars.keyboard.yCursor--;
                        break;


                }


            }

            break;


    }
    
}

CheckState Game::checkWord() {

    uint8_t guessWord[5];
    uint8_t testWord[5];
    uint8_t answer[5];
    
    for (uint8_t i = 0; i < 5; i++) {
        guessWord[i] = gamePlayVars.guesses.chars[gamePlayVars.guesses.yCursor][i];
        answer[i] = gamePlayVars.selectedWord[i];
        gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i] = GuessState::Incorrect;
    }


    // Is the word correct?

    bool isCorrectWord = true;

    for (uint8_t i = 0; i < 5; i++) {
        if (guessWord[i] != answer[i]) {
            isCorrectWord = false;
        }
    }
    
    if (isCorrectWord) {

        for (uint8_t i = 0; i < 5; i++) {
            gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i] = GuessState::Correct; 
        }

        return CheckState::CorrectWord;
    }
 

    // Get start of words using char one and two of guess ..

    uint32_t alphaStart = 0;
    uint16_t startPos = ((guessWord[0] - 65) * 26) + (guessWord[1] - 65);
    char status = ' ';

    switch (gamePlayVars.mode) {

        case GameMode::English:
            alphaStart = Dictionary::English_AlphaMap[startPos] * 6;
            break;

        case GameMode::French:
            alphaStart = Dictionary::French_AlphaMap[startPos] * 6;
            break;

    }

    while (true) {

        file.seek(alphaStart);
        file.read(&status, 1);
        file.read(&testWord, 5);

        alphaStart = alphaStart + 6;

        if (testWord[0] > guessWord[0] || (testWord[0] == guessWord[0] && testWord[1] > guessWord[1])) {
            
            return CheckState::InvalidWord;

        }


        // Valid word!  What are correct?

        bool isValid = true;

        for (uint8_t i = 0; i < 5; i++) {

            if (testWord[i] != guessWord[i]) {
                isValid = false;
                break;
            };

        }

        if (isValid) {

            
            // Correct letters ..

            for (uint8_t i = 0; i < 5; i++) {

                if (guessWord[i] == answer[i]) { 
                    gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i] = GuessState::Correct; 
                    answer[i] = ' ';
                }

            }

            for (uint8_t i = 0; i < 5; i++) {

                if (guessWord[i] != gamePlayVars.selectedWord[i]) { 

                    for (uint8_t j = 0; j < 5; j++) {

                        if (gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][j] != GuessState::Correct && testWord[i] == answer[j]) { 

                            gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i] = GuessState::WrongPosition;
                            answer[j] = ' ';
                            break;
                    
                        }
                    
                    }


                }

            }


            // If the letter is not found but already exists, we cannot remove it from the keyboard ..

            for (uint8_t i = 0; i < 5; i++) {

                if (gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i] == GuessState::Incorrect) {

                    for (uint8_t j = 0; j < 5; j++) {

                        if (guessWord[i] == gamePlayVars.selectedWord[j]) { 

                            gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i] = GuessState::Duplicate;
                    
                        }
                    
                    }

                }

            }


            // Disable the keys for letters not found in solution ..

            for (uint8_t i = 0; i < 5; i++) {

                switch (gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][i]) {

                    case GuessState::Incorrect: 
                        gamePlayVars.keyboard.keys[guessWord[i] - 65] = KeyState::Invisible;
                        break;

                    case GuessState::Correct: 
                        gamePlayVars.keyboard.keys[guessWord[i] - 65] = KeyState::Correct;
                        break;

                    case GuessState::WrongPosition: 
                        if (gamePlayVars.keyboard.keys[guessWord[i] - 65] == KeyState::Visible) {
                            gamePlayVars.keyboard.keys[guessWord[i] - 65] = KeyState::WrongPosition;
                        }
                        break;
            
                }

            }


            // Clear duplicate marks ..

            for (uint8_t j = 0; j < 5; j++) {

                if (gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][j] == GuessState::Duplicate) { 

                    gamePlayVars.guesses.state[gamePlayVars.guesses.yCursor][j] = GuessState::Incorrect;
            
                }
            
            }

            return CheckState::RealWord;

        }

    }

}
