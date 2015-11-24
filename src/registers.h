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

/* main register set */
byte RG_A; /* accumulator */
byte RG_B; /* general purpose */
byte RG_C; /* general purpose */
byte RG_D; /* general purpose */
byte RG_E; /* general purpose */
byte RG_F; /* flags */
byte RG_H; /* 16 bit - high order */
byte RG_L; /* 16 bit - low order */

/* alternate register set */
byte RG_A_; /* accumulator */
byte RG_B_; /* general purpose */
byte RG_C_; /* general purpose */
byte RG_D_; /* general purpose */
byte RG_E_; /* general purpose */
byte RG_F_; /* flags */
byte RG_H_; /* 16 bit - high order */
byte RG_L_; /* 16 bit - low order */

/* special registers */
byte RG_I; /* interrupt vector */
byte RG_R; /* memory refresh */

/* 16 bit registers */
word RG_IX; /* index register */
word RG_IY; /* index register */
word RG_SP; /* stack pointer */
word RG_PC; /* program counter */

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
void AddA(byte n);
word GetPC(word inc);
void AddPC(word nn);

#endif
