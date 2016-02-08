#include "instructionset.h"

/*
 * Generic function wrappers for operations
 */

void op_add(byte* src, byte* dst, int carry) {
    /* set carry flag */
    if((*dst + *src) & MAXBYTE != *dst + *src) setFlag(FLAG_C, 1);
    else setFlag(FLAG_C, 0);

    /* perform operation */
    *dst = (*dst + *src) & MAXBYTE;
    if(carry) *dst++;

    /* check if result zero */
    if(*dst == 0) setFlag(FLAG_Z, 1);
    else setFlag(FLAG_Z, 0);

    /* operation not subtraction, clear N */
    setFlag(FLAG_N, 0);

    /* set sign flag */
    setFlag(FLAG_S, (*dst & 0b10000000) >> 8);

    /* create bit copies in F3/5 */
    setFlag(FLAG_F3, (*dst & 0b00000100) >> 3);
    setFlag(FLAG_F5, (*dst & 0b00010000) >> 5);
}

void op_add16(word* src, word* dst, int carry) {
    /* set carry flag */
    if((*dst + *src) & MAXWORD != *dst + * src) setFlag(FLAG_C, 1);
    else setFlag(FLAG_C, 0);

    /* perform operation */
    *dst = (*dst + *src) & MAXWORD;
    if(carry) *dst++;

    /* check if result zero */
    if(*dst == 0) setFlag(FLAG_Z, 1);
    else setFlag(FLAG_Z, 0);

    /* operation not subtraction */
    setFlag(FLAG_N, 0);

    /* set sign flag */
    setFlag(FLAG_S, (*dst & 0b1000000000000000) >> 16);

    /* create bit copies in F3/5 */
    setFlag(FLAG_F3, (*dst & 0b0000000000000100) >> 3);
    setFlag(FLAG_F5, (*dst & 0b0000000000010000) >> 5);
}

void op_ld(byte* src, byte* dst) {
    /* perform operation */
    *dst = *src;

    /* set zero flag */
    if(*dst == 0) setFlag(FLAG_Z, 1);
    else setFlag(FLAG_Z, 0);

    /* operation not subtraction, clear N */
    setFlag(FLAG_N, 0);

    /* set sign flag */
    setFlag(FLAG_S, (*dst & 0b10000000) >> 8);

    /* create bit copies in F3/5 */
    setFlag(FLAG_F3, (*dst & 0b00000100) >> 3);
    setFlag(FLAG_F5, (*dst & 0b00010000) >> 5);
}

void op_ld16(word* src, word* dst) {
    /* perform operation */
    *dst = *src;

    /* set zero flag */
    if(*dst == 0) setFlag(FLAG_Z, 1);
    else setFlag(FLAG_Z, 0);

    /* operation not subtraction, clear N */
    setFlag(FLAG_N, 0);

    /* set sign flag */
    setFlag(FLAG_S, (*dst & 0b1000000000000000) >> 16);

    /* create bit copies in F3/5 */
    setFlag(FLAG_F3, (*dst & 0b0000000000000100) >> 3);
    setFlag(FLAG_F5, (*dst & 0b0000000000010000) >> 5);
}

void op_sub(byte* src, byte* dst, int carry) {
    /* perform operation*/
    *dst -= *src;
    if(carry) *dst--;

    /* operation is subtraction, set N */
    setFlag(FLAG_N, 1);

    /* set sign flag */
    setFlag(FLAG_S, (*dst & 0b10000000) >> 8);

    /* create bit copies in F3/5 */
    setFlag(FLAG_F3, (*dst & 0b00000100) >> 3);
    setFlag(FLAG_F5, (*dst & 0b00010000) >> 5);
}

/*
 * Executes a single instruction at the current program counter.
 * Increases the program counter and cycle count registers somewhat.
 * Uses a large switch statement as this is turned into a jump table
 * by the compiler, (i.e. very efficient).
 */
void exec(void) {
    switch(RAM[GetPC(1)]) {
        case OP_NOP:
            AddR(4);
            break;

        case OP_LD_BC_NN:
            op_ld16(&RG_BC, (word*)&RAM[GetPC(2)]);
            AddR(10);
            break;

        case OP_LD_BCa_NN:
            op_ld16((word*)&RAM[RG_BC], (word*)&RAM[GetPC(2)]);
            AddR(7);
            break;

        case OP_LD_B_N:
            op_ld(RG_B, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_ADD_HL_BC:
            op_add16(&RG_HL, &RG_BC, 0);
            AddR(11);
            break;

        case OP_LD_A_BCa:
            op_ld(RG_A, &RAM[BC2word()]);
            AddR(7);
            break;

        case OP_LD_C_N:
            op_ld(RG_C, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_LD_DE_NN:
            op_ld16(&RG_DE, (word*)&RAM[GetPC(2)]);
            AddR(10);
            break;

        case OP_LD_DEa_A:
            op_ld(&RAM[RG_DE], RG_A);
            AddR(7);
            break;

        case OP_LD_D_N:
            op_ld(RG_D, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_ADD_HL_DE:
            op_add16(&RG_HL, &RG_DE, 0);
            AddR(11);
            break;

        case OP_LD_E_N:
            op_ld(RG_E, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_LD_HL_NN:
            op_ld16(&RG_HL, (word*)&RAM[GetPC(2)]);
            AddR(10);
            break;

        case OP_LD_NNa_HL:
            op_ld16((word*)&RAM[GetRAMword(GetPC(2))], &RG_HL);
            AddR(16);
            break;

        case OP_LD_H_N:
            op_ld(RG_H, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_ADD_HL_HL:
            op_add16(&RG_HL, &RG_HL, 0);
            AddR(11);
            break;

        case OP_LD_HL_NNa:
            op_ld16(&RG_HL, (word*)&RAM[GetRAMword(GetPC(2))]);
            AddR(16);
            break;

        case OP_LD_L_N:
            op_ld(RG_L, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_LD_SP_NN:
            op_ld16(&RG_SP, (word*)&RAM[GetPC(2)]);
            AddR(10);
            break;

        case OP_LD_NNa_A:
            op_ld(&RAM[GetRAMword(GetPC(2))], RG_A);
            AddR(13);
            break;

        case OP_LD_HLa_N:
            op_ld(&RAM[RG_HL], &RAM[GetPC(1)]);
            AddR(10);
            break;

        case OP_ADD_HL_SP:
            op_add16(&RG_HL, &RG_SP, 0);
            AddR(11);
            break;

        case OP_LD_A_NNa:
            op_ld(RG_A, &RAM[GetRAMword(GetPC(2))]);
            AddR(13);
            break;

        case OP_LD_A_N:
            op_ld(RG_A, &RAM[GetPC(1)]);
            AddR(7);
            break;

        case OP_LD_B_B:
            op_ld(RG_B, RG_B);
            AddR(4);
            break;

        case OP_LD_B_C:
            op_ld(RG_B, RG_C);
            AddR(4);
            break;

        case OP_LD_B_D:
            op_ld(RG_B, RG_D);
            AddR(4);
            break;

        case OP_LD_B_E:
            op_ld(RG_B, RG_E);
            AddR(4);
            break;

        case OP_LD_B_H:
            op_ld(RG_B, RG_H);
            AddR(4);
            break;

        case OP_LD_B_L:
            op_ld(RG_B, RG_L);
            AddR(4);
            break;

        case OP_LD_B_HLa:
            op_ld(RG_B, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_B_A:
            op_ld(RG_B, RG_A);
            AddR(4);
            break;

        case OP_LD_C_B:
            op_ld(RG_C, RG_B);
            AddR(4);
            break;

        case OP_LD_C_C:
            op_ld(RG_C, RG_C);
            AddR(4);
            break;

        case OP_LD_C_D:
            op_ld(RG_C, RG_D);
            AddR(4);
            break;

        case OP_LD_C_E:
            op_ld(RG_C, RG_E);
            AddR(4);
            break;

        case OP_LD_C_H:
            op_ld(RG_C, RG_H);
            AddR(4);
            break;

        case OP_LD_C_L:
            op_ld(RG_C, RG_L);
            AddR(4);
            break;

        case OP_LD_C_HLa:
            op_ld(RG_C, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_C_A:
            op_ld(RG_C, RG_A);
            AddR(4);
            break;

        case OP_LD_D_B:
            op_ld(RG_D, RG_B);
            AddR(4);
            break;

        case OP_LD_D_C:
            op_ld(RG_D, RG_C);
            AddR(4);
            break;

        case OP_LD_D_D:
            op_ld(RG_D, RG_D);
            AddR(4);
            break;

        case OP_LD_D_E:
            op_ld(RG_D, RG_E);
            AddR(4);
            break;

        case OP_LD_D_H:
            op_ld(RG_D, RG_H);
            AddR(4);
            break;

        case OP_LD_D_L:
            op_ld(RG_D, RG_L);
            AddR(4);
            break;

        case OP_LD_D_HLa:
            op_ld(RG_D, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_D_A:
            op_ld(RG_D, RG_A);
            AddR(4);
            break;

        case OP_LD_E_B:
            op_ld(RG_E, RG_B);
            AddR(4);
            break;

        case OP_LD_E_C:
            op_ld(RG_E, RG_C);
            AddR(4);
            break;

        case OP_LD_E_D:
            op_ld(RG_E, RG_D);
            AddR(4);
            break;

        case OP_LD_E_E:
            op_ld(RG_E, RG_E);
            AddR(4);
            break;

        case OP_LD_E_H:
            op_ld(RG_E, RG_H);
            AddR(4);
            break;

        case OP_LD_E_L:
            op_ld(RG_E, RG_L);
            AddR(4);
            break;

        case OP_LD_E_HLa:
            op_ld(RG_E, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_E_A:
            op_ld(RG_E, RG_A);
            AddR(4);
            break;

        case OP_LD_H_B:
            op_ld(RG_H, RG_B);
            AddR(4);
            break;

        case OP_LD_H_C:
            op_ld(RG_H, RG_C);
            AddR(4);
            break;

        case OP_LD_H_D:
            op_ld(RG_H, RG_D);
            AddR(4);
            break;

        case OP_LD_H_E:
            op_ld(RG_H, RG_E);
            AddR(4);
            break;

        case OP_LD_H_H:
            op_ld(RG_H, RG_H);
            AddR(4);
            break;

        case OP_LD_H_L:
            op_ld(RG_H, RG_L);
            AddR(4);
            break;

        case OP_LD_H_HLa:
            op_ld(RG_H, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_H_A:
            op_ld(RG_H, RG_A);
            AddR(4);
            break;

        case OP_LD_L_B:
            op_ld(RG_L, RG_B);
            AddR(4);
            break;

        case OP_LD_L_C:
            op_ld(RG_L, RG_C);
            AddR(4);
            break;

        case OP_LD_L_D:
            op_ld(RG_L, RG_D);
            AddR(4);
            break;

        case OP_LD_L_E:
            op_ld(RG_L, RG_E);
            AddR(4);
            break;

        case OP_LD_L_H:
            op_ld(RG_L, RG_H);
            AddR(4);
            break;

        case OP_LD_L_L:
            op_ld(RG_L, RG_L);
            AddR(4);
            break;

        case OP_LD_L_HLa:
            op_ld(RG_L, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_L_A:
            op_ld(RG_L, RG_A);
            AddR(4);
            break;

        case OP_LD_HLa_B:
            op_ld(&RAM[RG_HL], RG_B);
            AddR(4);
            break;

        case OP_LD_HLa_C:
            op_ld(&RAM[RG_HL], RG_C);
            AddR(4);
            break;

        case OP_LD_HLa_D:
            op_ld(&RAM[RG_HL], RG_D);
            AddR(4);
            break;

        case OP_LD_HLa_E:
            op_ld(&RAM[RG_HL], RG_E);
            AddR(4);
            break;

        case OP_LD_HLa_H:
            op_ld(&RAM[RG_HL], RG_H);
            AddR(4);
            break;

        case OP_LD_HLa_L:
            op_ld(&RAM[RG_HL], RG_L);
            AddR(4);
            break;

        case OP_LD_HLa_A:
            op_ld(&RAM[RG_HL], RG_A);
            AddR(4);
            break;

        case OP_HALT:
            /* TODO: implement halt simulation */
            break;

        case OP_LD_A_B:
            op_ld(RG_A, RG_B);
            AddR(4);
            break;

        case OP_LD_A_C:
            op_ld(RG_A, RG_C);
            AddR(4);
            break;

        case OP_LD_A_D:
            op_ld(RG_A, RG_D);
            AddR(4);
            break;

        case OP_LD_A_E:
            op_ld(RG_A, RG_E);
            AddR(4);
            break;

        case OP_LD_A_H:
            op_ld(RG_A, RG_H);
            AddR(4);
            break;

        case OP_LD_A_L:
            op_ld(RG_A, RG_L);
            AddR(4);
            break;

        case OP_LD_A_HLa:
            op_ld(RG_A, &RAM[RG_HL]);
            AddR(7);
            break;

        case OP_LD_A_A:
            op_ld(RG_A, RG_A);
            AddR(4);
            break;

        case OP_ADD_A_B:
            op_add(RG_A, RG_B, 0);
            AddR(4);
            break;

        case OP_ADD_A_C:
            op_add(RG_A, RG_C, 0);
            AddR(4);
            break;

        case OP_ADD_A_D:
            op_add(RG_A, RG_D, 0);
            AddR(4);
            break;

        case OP_ADD_A_E:
            op_add(RG_A, RG_E, 0);
            AddR(4);
            break;

        case OP_ADD_A_H:
            op_add(RG_A, RG_H, 0);
            AddR(4);
            break;

        case OP_ADD_A_L:
            op_add(RG_A, RG_L, 0);
            AddR(4);
            break;

        case OP_ADD_A_HLa:
            op_add(RG_A, &RAM[RG_HL], 0);
            AddR(7);
            break;

        case OP_ADD_A_A:
            op_add(RG_A, RG_A, 0);
            AddR(4);
            break;

        case OP_ADC_A_B:
            op_add(RG_A, RG_B, 1);
            AddR(4);
            break;

        case OP_ADC_A_C:
            op_add(RG_A, RG_C, 1);
            AddR(4);
            break;

        case OP_ADC_A_D:
            op_add(RG_A, RG_D, 1);
            AddR(4);
            break;

        case OP_ADC_A_E:
            op_add(RG_A, RG_E, 1);
            AddR(4);
            break;

        case OP_ADC_A_H:
            op_add(RG_A, RG_H, 1);
            AddR(4);
            break;

        case OP_ADC_A_L:
            op_add(RG_A, RG_L, 1);
            AddR(4);
            break;

        case OP_ADC_A_HLa:
            op_add(RG_A, &RAM[RG_HL], 1);
            AddR(7);
            break;

        case OP_ADC_A_A:
            op_add(RG_A, RG_A, 1);
            AddR(4);
            break;

        case OP_SUB_A_B:
            op_sub(RG_A, RG_B, 0);
            AddR(4);
            break;

        case OP_SUB_A_C:
            op_sub(RG_A, RG_C, 0);
            AddR(4);
            break;

        case OP_SUB_A_D:
            op_sub(RG_A, RG_D, 0);
            AddR(4);
            break;

        case OP_SUB_A_E:
            op_sub(RG_A, RG_E, 0);
            AddR(4);
            break;

        case OP_SUB_A_H:
            op_sub(RG_A, RG_H, 0);
            AddR(4);
            break;

        case OP_SUB_A_L:
            op_sub(RG_A, RG_L, 0);
            AddR(4);
            break;

        case OP_SUB_A_HLa:
            op_sub(RG_A, &RAM[RG_HL], 0);
            AddR(7);
            break;

        case OP_SUB_A_A:
            op_sub(RG_A, RG_A, 0);
            AddR(4);
            break;


        case OP_SBC_A_B:
            op_sub(RG_A, RG_B, 1);
            AddR(4);
            break;

        case OP_SBC_A_C:
            op_sub(RG_A, RG_C, 1);
            AddR(4);
            break;

        case OP_SBC_A_D:
            op_sub(RG_A, RG_D, 1);
            AddR(4);
            break;

        case OP_SBC_A_E:
            op_sub(RG_A, RG_E, 1);
            AddR(4);
            break;

        case OP_SBC_A_H:
            op_sub(RG_A, RG_H, 1);
            AddR(4);
            break;

        case OP_SBC_A_L:
            op_sub(RG_A, RG_L, 1);
            AddR(4);
            break;

        case OP_SBC_A_HLa:
            op_sub(RG_A, &RAM[GetRAMword(RG_HL)], 1);
            AddR(7);
            break;

        case OP_SBC_A_A:
            op_sub(RG_A, RG_A, 1);
            AddR(4);
            break;

        case OP_AND_B:
            *RG_A &= *RG_B;
            AddR(4);
            break;

        case OP_AND_C:
            *RG_A &= *RG_C;
            AddR(4);
            break;

        case OP_AND_D:
            *RG_A &= *RG_D;
            AddR(4);
            break;

        case OP_AND_E:
            *RG_A &= *RG_E;
            AddR(4);
            break;

        case OP_AND_H:
            *RG_A &= *RG_H;
            AddR(4);
            break;

        case OP_AND_L:
            *RG_A &= *RG_L;
            AddR(4);
            break;

        case OP_AND_HLa:
            *RG_A &= GetRAMbyte(RG_HL);
            AddR(7);
            break;

        case OP_AND_A:
            *RG_A &= *RG_A;
            AddR(4);
            break;

        case OP_XOR_B:
            *RG_A ^= *RG_B;
            AddR(4);
            break;

        case OP_XOR_C:
            *RG_A ^= *RG_C;
            AddR(4);
            break;

        case OP_XOR_D:
            *RG_A ^= *RG_D;
            AddR(4);
            break;

        case OP_XOR_E:
            *RG_A ^= *RG_E;
            AddR(4);
            break;

        case OP_XOR_H:
            *RG_A ^=  *RG_H;
            AddR(4);
            break;

        case OP_XOR_L:
            *RG_A ^= *RG_L;
            AddR(4);
            break;

        case OP_XOR_HLa:
            *RG_A ^= GetRAMbyte(RG_HL);
            AddR(7);
            break;

        case OP_XOR_A:
            *RG_A ^= *RG_A;
            AddR(4);
            break;

        case OP_OR_B:
            *RG_A |= *RG_B;
            AddR(4);
            break;

        case OP_OR_C:
            *RG_A |= *RG_B;
            AddR(4);
            break;

        case OP_OR_D:
            *RG_A |= *RG_D;
            AddR(4);
            break;

        case OP_OR_E:
            *RG_A |= *RG_E;
            AddR(4);
            break;

        case OP_OR_H:
            *RG_A |= *RG_H;
            AddR(4);
            break;

        case OP_OR_L:
            *RG_A |= *RG_L;
            AddR(4);
            break;

        case OP_OR_HLa:
            *RG_A |= GetRAMbyte(RG_HL);
            AddR(7);
            break;

        case OP_OR_A:
            *RG_A |= *RG_A;
            AddR(4);
            break;

        case OP_ADD_A_N:
            op_add(RG_A, &RAM[GetPC(1)], 0);
            AddR(7);
            break;

        case OP_ADC_A_N:
            op_add(RG_A, &RAM[GetPC(1)], 1);
            AddR(7);
            break;

        case OP_AND_N:
            *RG_A &= GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_XOR_N:
            *RG_A ^= GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_OR_N:
            *RG_A |= GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        default:
            /* TODO: complain here */
            break;
    }
}
