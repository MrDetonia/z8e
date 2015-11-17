/*
 * z8e by Zac Herd
 * ---------------
 *  Copyright 2015, Zac Herd
 *  Licensed under BSD 3-clause License
 *  See LICENSE for more info
 *
 */

#include "memory.h"

byte RAM[MEMSIZE];

word bytes2word(byte H, byte L) {
    return H << BYTELEN | L;
}

void SetRAMbyte(word addr, byte src) {
    RAM[addr] = src;
}

void SetRAMword(word addr, word src) {
    RAM[addr] = src & MAXBYTE;
    RAM[addr++] = (src >> BYTELEN) & MAXBYTE;
}

byte GetRAMbyte(word addr) {
    return RAM[addr];
}

word GetRAMword(word addr) {
    return bytes2word(RAM[addr + 1], RAM[addr]);
}
