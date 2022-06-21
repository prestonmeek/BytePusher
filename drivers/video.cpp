#include <SDL2/SDL.h>
#include "video.h"

using namespace std;

Video::Video() {
    // set up window stuff
    window = SDL_CreateWindow(
        "BytePusher",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    // set up graphical stuff
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT 
    );
}

unsigned int Video::readVideoMem(unsigned char row, unsigned char column) {
    return gfx[row][column];
}

void Video::writeVideoMem(unsigned char row, unsigned char column, unsigned int data) {
    gfx[row][column] = data;
}

void Video::render() {
    SDL_RenderClear(renderer);

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // get the pixel color in rgb form
            int blue;
            int red;
            int green;

            unsigned int color = readVideoMem(i, j);

            if (color < 216) {
                blue = color % 6;
                green = ((color - blue) / 6) % 6;
                red = ((((color - blue) / 6) - green) / 6) % 6;
            } else {
                blue = 0;
                green = 0;
                red = 0;
            }

            // to get data in RGB format, must multiply by 0x33
            red   *= 0x33;
            green *= 0x33;
            blue  *= 0x33;

            // data is in form of ARGB (alpha, red, green, blue)
            writeVideoMem(i, j, 0xFF000000 | (red << 16) | (green << 8) | blue);
        }
    }

    int pitch = SCREEN_WIDTH * 4;

    // update the texture with the pixel array
    SDL_UpdateTexture(texture, NULL, &gfx, pitch);

    // load the texture to the screen
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);      
}

void Video::shutup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
}