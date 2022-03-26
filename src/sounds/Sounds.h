#pragma once

#include <LibAudio>
#include "../Utils/SFXVolumeSource.hpp"
#include "Success.h"
#include "Ding_00.h"
#include "Ding_01.h"
#include "Ding_02.h"
#include "Ding_03.h"

struct Sounds {

    File mainThemeFile;
    File soundEffectFile;
    Audio::RAWFileSource *music;

    uint8_t themeToPlay_Next = 255;
    SoundSettings soundSettings_Next;
    FadeMode fadeMode = FadeMode::None;

    static inline uint16_t volume = 255;

    void connectVolumeControl(uint32_t lastChannel){
        Audio::connect(
            lastChannel,
            nullptr,
            +[](uint8_t *buffer, void *){
                for(int16_t i=0; i<512; ++i) 
                    buffer[i] = buffer[i] * volume >> 8;
            }
        );
    }

    enum class Effects : uint8_t {
        Success,
        Ding_00,
        Ding_01,
        Ding_02,
        Ding_03,
    };

    void updateFades() {

        switch (this->fadeMode) {

            case FadeMode::FadeIn:
                volume = volume + 8;
                if (volume >= 247) {
                    volume = 255;
                    this->fadeMode = FadeMode::None;
                }
                break;

            case FadeMode::FadeOut:

                volume = volume - 8;

                if (volume <= 8) {
                    
                    this->volume = 0;

                    if (this->themeToPlay_Next != 255) {
                        this->fadeMode = FadeMode::FadeIn;
                        this->playTheme(this->themeToPlay_Next, this->soundSettings_Next);
                    }
                    else {
                        this->fadeMode = FadeMode::None;
                    }

                }
                break;

            default: break;

        }

    }



    // Sound effects.

    void playTheme(uint8_t themeToPlay, SoundSettings soundSettings, bool ignoreFadeOut = false, bool ensureFullVolume = false) {

        constexpr char sounds[3][19] = { "music/LeWord02.raw", "music/LeWord03.raw", "music/LeWord04.raw" };

        if (volume > 0 && !ignoreFadeOut) {

            this->fadeMode = FadeMode::FadeOut;
            this->themeToPlay_Next = themeToPlay;
            this->soundSettings_Next = soundSettings;

        }
        else {

            this->themeToPlay_Next = 255;

            if (ensureFullVolume) volume = 255;

            switch (soundSettings) {

                case SoundSettings::Music:
                case SoundSettings::Both:

                    if (this->mainThemeFile.openRO(sounds[themeToPlay])) {
                        auto& music = Audio::play<0>(this->mainThemeFile);
                        
                        if (themeToPlay <= 2) {
                            music.setLoop(true);
                        }
                        else {
                            music.setLoop(false);
                        }

                    }

                    break;

                case SoundSettings::SFX:
                case SoundSettings::None:
        
                    Audio::stop<0>();
                    break;

            }

        }

    }

    void muteTheme() {

        Audio::stop<0>();        
        
    }

    void playSoundEffect(Sounds::Effects soundEffect, SoundSettings soundSettings) {

        switch (soundSettings) {

            case SoundSettings::SFX:
            case SoundSettings::Both:

                switch (soundEffect) {
                    
                    case Sounds::Effects::Success:
                        Audio::play<2>(sfx_Success, 255, 1);        
                        break;
                    
                    case Sounds::Effects::Ding_00:
                        Audio::play<2>(sfx_Ding_00, 255, 1);        
                        break;
                    
                    case Sounds::Effects::Ding_01:
                        Audio::play<2>(sfx_Ding_01, 255, 1);        
                        break;
                    
                    case Sounds::Effects::Ding_02:
                        Audio::play<2>(sfx_Ding_02, 255, 1);        
                        break;
                    
                    case Sounds::Effects::Ding_03:
                        Audio::play<2>(sfx_Ding_03, 255, 1);        
                        break;

                }

                break;

            default: break;

        }

    }    
    
};