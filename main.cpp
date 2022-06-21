#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <SDL2/SDL.h>
#include "cpu.h"

using namespace std;
using namespace chrono;

const int SCREEN_WIDTH  = 256;
const int SCREEN_HEIGHT = 256;

void printFPS() {
    static time_point<steady_clock> oldTime = high_resolution_clock::now();
    static int fps; fps++;

    if (duration_cast<seconds>(high_resolution_clock::now() - oldTime) >= seconds{1}) {
        oldTime = high_resolution_clock::now();
        cout << "FPS: " << fps <<  endl;
        fps = 0;
    }
}

// TODO: add vsync perhaps?
int main(int argc, char** argv) {
    // before we set up anything, init everything
    SDL_Init(SDL_INIT_EVERYTHING);

    CPU BytePusher;

    if (!argv[1])
        BytePusher.loadGame("./games/nyan.bp");
    else
        BytePusher.loadGame("./games/" + string(argv[1]));

    bool keepWindowOpen = true;

    // init frame rate stuff
    system_clock::time_point a = system_clock::now();
    system_clock::time_point b = system_clock::now();

    while (keepWindowOpen) {
        // run at 60 fps
        a = system_clock::now();
        duration<double, milli> work_time = a - b;

        // run instructions n such
        BytePusher.cycle();

        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    BytePusher.shutupDrivers();     // turn off drivers
                    keepWindowOpen = false;
                break;

                case SDL_KEYDOWN:
                    BytePusher.writeKeyPresses(e);
                break;

                case SDL_KEYUP:
                    BytePusher.writeKeyPresses(e);
                break;

            }
        }

        // render
        BytePusher.render();

        // debug
        // printFPS();

        // 1000.0 / 60.0 = 60fps
        if (work_time.count() < (1000.0 / 60.0)) {
            duration<double, milli> delta_ms((1000.0 / 60.0) - work_time.count());
            auto delta_ms_duration = duration_cast<milliseconds>(delta_ms);
            this_thread::sleep_for(milliseconds(delta_ms_duration.count()));
        }

        b = system_clock::now();
        duration<double, milli> sleep_time = b - a;
    }

    return 0;
}