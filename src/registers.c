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
    return RG_F & (0b1 << flag);
}

void setFlag(const byte flag, byte val) {
    byte bitmask = (val & 0b1) << flag;
    RG_F = (RG_F & ~(0b1 << flag)) & bitmask;
}

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
    RG_B = (nn & MAXBYTE << BYTELEN) >> BYTELEN;
    RG_C = nn & MAXBYTE;
}

void SetDE(word nn) {
    RG_D = (nn & MAXBYTE << BYTELEN) >> BYTELEN;
    RG_E = nn & MAXBYTE;
}

void SetHL(word nn) {
    RG_H = (nn & MAXBYTE << BYTELEN) >> BYTELEN;
    RG_L = nn & MAXBYTE;
}

void AddR(byte n) {
    RG_R = (RG_R + n) & MAXBYTE;
}

void AddA(byte n, int carry) {
    if(carry) {
        if((RG_A + n) & MAXBYTE != RG_A + n) RG_F |= 0b1000000;
        else RG_F &= 0b01111111;
    }
    RG_A = (RG_A + n) & MAXBYTE;
}

word GetPC(word inc) {
    word tmp = RG_PC;
    AddPC(inc);
    return tmp;
}

void AddPC(word nn) {
    RG_PC = (RG_PC + nn) & MAXWORD;
}
