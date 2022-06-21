#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>
#include "cpu.h"

using namespace std;

CPU::CPU() {
    // reset the pc
    pc = 0;

    // reset memory
    for (int i = 0; i < 0x1000000; i++)
        ram.writeMem(i, 0);

    // reset vram
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++)
            video.writeVideoMem(i, j, 0);
    }
}

void CPU::loadGame(string path) {
    // open game file and get its size
    fstream game(path, fstream::in | fstream::binary | fstream::ate);
    int size = game.tellg();

    // set read position back to 0
    game.seekg(0);

    for (int i = 0; i < size; i++) {
        // read a byte and store it in this temp var
        char byte;
        game.read(&byte, 1);

        // write the byte to RAM
        ram.writeMem(i, byte);
    }

    cout << "Loaded game: \"" << path << "\"\n";
}

void CPU::writeKeyPresses(SDL_Event &e) {
    // write keyboard input info to memory
    unsigned short kbInput = kb.handleKeyInput(e);

    ram.writeMem(0, kbInput >> 8);
    ram.writeMem(1, kbInput & 0xFF);
}

void CPU::cycle() {
    // set the pc equal to the data at address 2
    pc = (ram.readMem(2) << 16) | (ram.readMem(3) << 8) | (ram.readMem(4));

    // execute exactly 65536 instructions
    for (int i = 0; i < 65536; i++) {
        // get the 3 big-endian 24-bit addresses: A, B, and C
        int A = (ram.readMem(pc + 0) << 16) | (ram.readMem(pc + 1) << 8) + (ram.readMem(pc + 2));
        int B = (ram.readMem(pc + 3) << 16) | (ram.readMem(pc + 4) << 8) + (ram.readMem(pc + 5));
        int C = (ram.readMem(pc + 6) << 16) | (ram.readMem(pc + 7) << 8) + (ram.readMem(pc + 8));

        ram.writeMem(B, ram.readMem(A));

        pc = C;
    }

    // write the graphical data designated by the byte at address 5
    // A value of ZZ means: pixel(XX, YY) is at address ZZYYXX.
    int loc = ram.readMem(5) << 16;

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++)
            video.writeVideoMem(i, j, ram.readMem(loc | (i << 8) | j));
    }

    // handle sound data designated by the two bytes at address 6
    // A value of XXYY means: audio sample ZZ is at address XXYYZZ.
    // audio sample size is 256 bytes
    loc = (ram.readMem(6) << 16) | (ram.readMem(7) << 8);

    for (int i = 0; i < 256; i++)
        audio.queueAudio(ram.readMem(loc | i));
}

void CPU::render() {
    video.render();
}

void CPU::shutupDrivers() {
    audio.shutup();
    video.shutup();
}