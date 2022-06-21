#include <string>
#include "keyboard.h"

using namespace std;

unsigned short Keyboard::handleKeyInput(SDL_Event &e) {
    SDL_Keycode *key  = find(begin(keys), end(keys), e.key.keysym.sym);
    unsigned char pos = distance(keys, key);

    // if keypress is invalid, return 
    if (key == end(keys))
        return kbInput;

    if (e.type == SDL_KEYDOWN)
        kbInput |= short(pow(2, pos));
    else if (e.type == SDL_KEYUP)
        kbInput &= ~short(pow(2, pos));

    // cout << bitset<16>(kbInput) << endl;

    // return data so it can be written to memory
    return kbInput;
}