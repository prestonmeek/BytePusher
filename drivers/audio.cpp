#include <SDL2/SDL.h>
#include <iostream>
#include "audio.h"

using namespace std;

// must be static or else there are some weird seg faults
SDL_AudioDeviceID Audio::deviceID;
SDL_AudioSpec Audio::spec;

Audio::Audio() {
    // set up audio spec
    spec.freq = 15360;
    spec.format = AUDIO_S8;
    spec.channels = 1;
    spec.size = 1;

    // set up audio device
    deviceID = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);

    // clear old audio queue
    SDL_ClearQueuedAudio(deviceID);

    // unpause audio
    SDL_PauseAudioDevice(deviceID, 0);
}

void Audio::queueAudio(const unsigned char &byte) {
    // std::cout << byte << std::endl;
    SDL_QueueAudio(deviceID, &byte, 1);
}

void Audio::shutup() {
    SDL_CloseAudioDevice(deviceID);
}