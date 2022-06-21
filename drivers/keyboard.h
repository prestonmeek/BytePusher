#include <SDL2/SDL.h>

class Keyboard {
    private:
        unsigned short kbInput = 0b0;

        SDL_Keycode keys[16] = {
            SDLK_0,
            SDLK_1,
            SDLK_2,
            SDLK_3,
            SDLK_4,
            SDLK_5,
            SDLK_6,
            SDLK_7,
            SDLK_8,
            SDLK_9,
            SDLK_a,
            SDLK_b,
            SDLK_c,
            SDLK_d,
            SDLK_e,
            SDLK_f
        };

       /*
       const SDL_Scancode keyboard[16] = {
           SDL_SCANCODE_0,
           SDL_SCANCODE_1,
           SDL_SCANCODE_2,
           SDL_SCANCODE_3,
           SDL_SCANCODE_4,
           SDL_SCANCODE_5,
           SDL_SCANCODE_6,
           SDL_SCANCODE_7,
           SDL_SCANCODE_8,
           SDL_SCANCODE_9,
           SDL_SCANCODE_A,
           SDL_SCANCODE_B,
           SDL_SCANCODE_C,
           SDL_SCANCODE_D,
           SDL_SCANCODE_E,
           SDL_SCANCODE_F,
       };
       */

    public:
        unsigned short handleKeyInput(SDL_Event &e);
};