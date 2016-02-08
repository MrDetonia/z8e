/*
 * z8e by Zac Herd
 * ---------------
 *  Copyright 2015, Zac Herd
 *  Licensed under BSD 3-clause License
 *  See LICENSE for more info
 *
 */

#ifndef _z8e_REGISTERS
#define _z8e_REGISTERS

#include "common.h"
#include "memory.h"

/* 16 bit registers */
word RG_AF;
word RG_BC;
word RG_DE;
word RG_HL;

/* main register set */
byte* RG_A = (byte*)&RG_AF;     /* accumulator */
byte* RG_B = (byte*)&RG_BC;     /* general purpose */
byte* RG_C = (byte*)&RG_BC + 1; /* general purpose */
byte* RG_D = (byte*)&RG_DE;     /* general purpose */
byte* RG_E = (byte*)&RG_DE + 1; /* general purpose */
byte* RG_F = (byte*)&RG_AF + 1; /* flags */
byte* RG_H = (byte*)&RG_HL;     /* 16 bit - high order */
byte* RG_L = (byte*)&RG_HL + 1; /* 16 bit - low order */

/* special registers */
byte RG_I; /* interrupt vector */
byte RG_R; /* memory refresh */

/* 16 bit registers */
word RG_IX; /* index register */
word RG_IY; /* index register */
word RG_SP; /* stack pointer */
word RG_PC; /* program counter */

/* flags */
enum {
    FLAG_C = 0,
    FLAG_N,
    FLAG_PV,
    FLAG_F3,
    FLAG_H,
    FLAG_F5,
    FLAG_Z,
    FLAG_S
} flags;

/* get value of flag */
byte getFlag(const byte flag);

/* set flag */
void setFlag(const byte flag, byte val);

/* functions to get multiple registers as words */
word BC2word(void);
word DE2word(void);
word HL2word(void);

/* functions to set 16 bit registers */
void SetBC(word nn);
void SetDE(word nn);
void SetHL(word nn);

/* common register increment/addition functions */
void AddR(byte n);
void AddA(byte n, int carry);
word GetPC(word inc);
void AddPC(word nn);

#endif
