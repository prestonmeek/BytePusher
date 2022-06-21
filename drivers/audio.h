class Audio {
    private:
        static SDL_AudioDeviceID deviceID;
        static SDL_AudioSpec spec;

    public:
        Audio();

        void queueAudio(const unsigned char &byte);

        void shutup();
};