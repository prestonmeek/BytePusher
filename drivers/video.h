#include <SDL2/SDL.h>

class Video {
    private:
        const int SCREEN_WIDTH  = 256;
        const int SCREEN_HEIGHT = 256;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;

        unsigned int gfx[256][256];

    public:
        Video();

        unsigned int readVideoMem(unsigned char row, unsigned char column);
        void writeVideoMem(unsigned char row, unsigned char column, unsigned int data);

        void render();

        void shutup();
};