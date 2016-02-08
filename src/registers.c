/*
 * z8e by Zac Herd
 * ---------------
 *  Copyright 2015, Zac Herd
 *  Licensed under BSD 3-clause License
 *  See LICENSE for more info
 *
 */

#include "registers.h"

byte getFlag(const byte flag) {
    return *RG_F & (0b1 << flag);
}

void setFlag(const byte flag, byte val) {
    byte bitmask = (val & 0b1) << flag;
    *RG_F = (*RG_F & ~(0b1 << flag)) & bitmask;
}

void AddR(byte n) {
    RG_R = (RG_R + n) & MAXBYTE;
}

word GetPC(word inc) {
    word tmp = RG_PC;
    AddPC(inc);
    return tmp;
}

void AddPC(word nn) {
    RG_PC = (RG_PC + nn) & MAXWORD;
}
