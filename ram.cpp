#include <iostream>
#include "ram.h"

RAM::RAM() {
    mem.resize(0x1000000);
}

unsigned char RAM::readMem(const int &address) {
    return mem.at(address);
}

void RAM::writeMem(const int &address, const unsigned char &data) {
    mem.at(address) = data;
}