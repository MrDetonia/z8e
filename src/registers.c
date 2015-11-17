/*
 * z8e by Zac Herd
 * ---------------
 *  Copyright 2015, Zac Herd
 *  Licensed under BSD 3-clause License
 *  See LICENSE for more info
 *
 */

#include "registers.h"

word BC2word(void) {
    return (RG_B << BYTELEN) | RG_C;
}

word DE2word(void) {
    return (RG_D << BYTELEN) | RG_E;
}

word HL2word(void) {
    return (RG_H << BYTELEN) | RG_L;
}

void SetBC(word nn) {
    RG_B = (nn & 0xff00) >> BYTELEN;
    RG_C = nn & 0x00ff;
}

void SetDE(word nn) {
    RG_D = (nn & 0xff00) >> BYTELEN;
    RG_E = nn & 0x00ff;
}

void SetHL(word nn) {
    RG_H = (nn & 0xff00) >> BYTELEN;
    RG_L = nn & 0x00ff;
}

void AddR(byte n) {
    RG_R = (RG_R + n) & 0xff;
}

word GetPC(word inc) {
    word tmp = RG_PC;
    AddPC(inc);
    return tmp;
}

void AddPC(word nn) {
    RG_PC = (RG_PC + nn) & 0xffff;
}
