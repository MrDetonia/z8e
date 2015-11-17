/*
 * z8e by Zac Herd
 * ---------------
 *  Copyright 2015, Zac Herd
 *  Licensed under BSD 3-clause License
 *  See LICENSE for more info
 *
 */

#ifndef _z8e_MEMORY
#define _z8e_MEMORY

#include "common.h"

/* define bytes and words */
typedef uint8_t byte;
typedef uint16_t word;

/* explicit length of byte for shifting */
#define BYTELEN 8

/* max byte value */
#define MAXBYTE 0xFF

/* max word value */
#define MAXWORD 0xFFFF

/* amount of memory (default 16K) */
#define MEMSIZE 16000

/* array containing memory */
extern byte RAM[];

/* convert two bytes to a word */
word bytes2word(byte H, byte L);

/* functions to store values in RAM */
void SetRAMbyte(word addr, byte src);
void SetRAMword(word addr, word src);

/* functions to read values from RAM */
byte GetRAMbyte(word addr);
word GetRAMword(word addr);

#endif
