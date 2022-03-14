#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"
#include "Structs.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		GameMode gameMode;

		uint16_t gamesWon_EN = 0;
		uint16_t gamesPlayed_EN = 0;
		uint16_t currentStreak_EN = 0;
		uint16_t maxStreak_EN = 0;

		uint16_t gamesWon_FR = 0;
		uint16_t gamesPlayed_FR = 0;
		uint16_t currentStreak_FR = 0;
		uint16_t maxStreak_FR = 0;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->gamesWon_EN = 0;
			this->gamesPlayed_EN = 0;
			this->currentStreak_EN = 0;
			this->maxStreak_EN = 0;

			this->gamesWon_FR = 0;
			this->gamesPlayed_FR = 0;
			this->currentStreak_FR = 0;
			this->maxStreak_FR = 0;
			this->saveCookie();

		}

		void initialise(GameMode gameMode) {

			switch (gameMode) {

				case GameMode::English:

					this->initialised = COOKIE_INITIALISED;
					this->gamesWon_EN = 0;
					this->gamesPlayed_EN = 0;
					this->currentStreak_EN = 0;
					this->maxStreak_EN = 0;
					break;
				
				case GameMode::French:

					this->gamesWon_FR = 0;
					this->gamesPlayed_FR = 0;
					this->currentStreak_FR = 0;
					this->maxStreak_FR = 0;
					this->saveCookie();
					break;

			}

		}

		void increaseCorrectWords(GameMode gameMode) {

			if (gameMode == GameMode::English) {

				this->gamesWon_EN++;
				this->gamesPlayed_EN++;
				this->currentStreak_EN++;
				if (this->currentStreak_EN > this->maxStreak_EN) this->maxStreak_EN = this->currentStreak_EN;

			}
			else {

				this->gamesWon_FR++;
				this->gamesPlayed_FR++;
				this->currentStreak_FR++;
				if (this->currentStreak_FR > this->maxStreak_FR) this->maxStreak_FR = this->currentStreak_FR;

			}

			this->saveCookie();

		}

		void resetWiningStreak(GameMode gameMode) {

			uint16_t gamesPlayed = 0;
			uint16_t currentStreak = 0;

			if (gameMode == GameMode::English) {

				this->gamesPlayed_EN++;
				this->currentStreak_EN = 0;

			}
			else {

				this->gamesPlayed_FR++;
				this->currentStreak_FR = 0;

			}

			this->saveCookie();

		}

		void setMode(GameMode gameMode) {

			this->gameMode = gameMode;
			this->saveCookie();

		}


};