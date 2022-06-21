#include <chrono>
#include "ram.h"
#include "drivers/audio.h"
#include "drivers/video.h"
#include "drivers/keyboard.h"


using namespace std;
using namespace chrono;

/*

    NOTES:

    16 MiB RAM (0x1000000)
    256 x 256 pixel display
    Program Counter is 3 bytes
    Big Endian encoding

*/

class CPU {
    private:
        RAM ram;
        Video video;
        // Audio audio;
        Keyboard kb;
        unsigned int pc;

    public:
        CPU();

        Audio audio;

        void initDrivers();
        void loadGame(string path);

        void writeKeyPresses(SDL_Event &e);

        void cycle();
        void render();

        void shutupDrivers();
};