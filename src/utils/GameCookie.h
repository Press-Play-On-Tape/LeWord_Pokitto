#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"
#include "Structs.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
<<<<<<< Updated upstream
		Language Language;
=======
		uint8_t track;
>>>>>>> Stashed changes
		GameMode gameMode;
		SoundSettings sfx;

		uint16_t gamesWon_EN = 0;
		uint16_t gamesPlayed_EN = 0;
		uint16_t currentStreak_EN = 0;
		uint16_t maxStreak_EN = 0;
		uint16_t distribution_EN[6] = { 0, 0, 0, 0, 0, 0 };

		uint16_t gamesWon_FR = 0;
		uint16_t gamesPlayed_FR = 0;
		uint16_t currentStreak_FR = 0;
		uint16_t maxStreak_FR = 0;
		uint16_t distribution_FR[6] = { 0, 0, 0, 0, 0, 0 };

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
<<<<<<< Updated upstream

			this->language = Language::English;
			this->gameMode = GameMode::Single;
=======
			this->sfx = SoundSettings::Both;
>>>>>>> Stashed changes

			this->gamesWon_EN = 0;
			this->gamesPlayed_EN = 0;
			this->currentStreak_EN = 0;
			this->maxStreak_EN = 0;

			this->gamesWon_FR = 0;
			this->gamesPlayed_FR = 0;
			this->currentStreak_FR = 0;
			this->maxStreak_FR = 0;

			for (uint8_t i = 0; i < 6; i++) {

				this->distribution_EN[i] = 0;
				this->distribution_FR[i] = 0;

			}

			this->saveCookie();

		}

		void initialise(Language Language) {

			switch (Language) {

				case Language::English:

					this->initialised = COOKIE_INITIALISED;
					this->gamesWon_EN = 0;
					this->gamesPlayed_EN = 0;
					this->currentStreak_EN = 0;
					this->maxStreak_EN = 0;

					for (uint8_t i = 0; i < 6; i++) {
						this->distribution_EN[i] = 0;
					}

					break;
				
				case Language::French:

					this->gamesWon_FR = 0;
					this->gamesPlayed_FR = 0;
					this->currentStreak_FR = 0;
					this->maxStreak_FR = 0;
					this->saveCookie();

					for (uint8_t i = 0; i < 6; i++) {
						this->distribution_FR[i] = 0;
					}

					break;

			}

		}

		void increaseCorrectWords(Language Language, uint8_t numberOfGuesses) {

			if (Language == Language::English) {

				this->gamesWon_EN++;
				this->gamesPlayed_EN++;
				this->currentStreak_EN++;
				this->distribution_EN[numberOfGuesses]++;
				if (this->currentStreak_EN > this->maxStreak_EN) this->maxStreak_EN = this->currentStreak_EN;

			}
			else {

				this->gamesWon_FR++;
				this->gamesPlayed_FR++;
				this->currentStreak_FR++;
				this->distribution_FR[numberOfGuesses]++;
				if (this->currentStreak_FR > this->maxStreak_FR) this->maxStreak_FR = this->currentStreak_FR;

			}

			this->saveCookie();

		}

		void resetWiningStreak(Language Language) {

			uint16_t gamesPlayed = 0;
			uint16_t currentStreak = 0;

			if (Language == Language::English) {

				this->gamesPlayed_EN++;
				this->currentStreak_EN = 0;

			}
			else {

				this->gamesPlayed_FR++;
				this->currentStreak_FR = 0;

			}

			this->saveCookie();

		}

		void setMode(Language Language) {

			this->Language = Language;
			this->saveCookie();

		}

		uint8_t getPercent(Language Language, uint8_t val) {

			uint16_t high = 0;

			switch (Language) {

				case Language::English:

					for (uint8_t i = 0; i < 6; i++) {
						if (distribution_EN[i] > high) high = distribution_EN[i];
					}

					if (high == 0) return 0;

					return (distribution_EN[val] * 90 / high);

				case Language::French:

					for (uint8_t i = 0; i < 6; i++) {
						if (distribution_FR[i] > high) high = distribution_FR[i];
					}

					if (high == 0) return 0;

					return (distribution_FR[val] * 90 / high);

			}

			return 0;

		}

		uint16_t getPercentVal(Language Language, uint8_t val) {

			uint16_t high = 0;

			switch (Language) {

				case Language::English:

					return distribution_EN[val];

				case Language::French:

					return distribution_FR[val];

			}

			return 0;

		}


};